
from __future__ import division, print_function, absolute_import

import tensorflow as tf
import numpy as np
from PIL import Image
import matplotlib.pyplot as plt
import math
import sys
import time
import operator
from keras.datasets import fashion_mnist as mnist 
import pickle
import imageio
from subprocess import call
import os
import datetime

#import MNIST data
mnist_data = mnist.load_data() 

# Mode
training = True
loading = False
saving = False

## Files parameters
#load_foldername = './save/temp2'
#save_foldername = './save/temp2'
#
## Training Parameters
learning_rate = 0.001
#num_steps = 10000
#batch_size = 100
#
#display_steps = 50
#test_dataset_size = 100

kp = 0.95

# Network Parameters
num_hidden_1 = 128
num_hidden_2 = 64
num_hidden_3 = 32
num_hidden_4 = 16

num_arem_4 = 16
num_arem_3 = 16
num_arem_2 = 1
num_arem_1 = 16

ksize = 5
num_input = 784 # MNIST data input (img shape: 28*28)

# Tensors placeholders
X = tf.placeholder("float", [None, 28,28,1])
Y = tf.placeholder("float", [None, 8,8,1])
keep_prob = tf.placeholder("float", [2])

# Encoder
w_enc = {
    'conv1':  tf.Variable(tf.random_normal([ksize, ksize, 1, num_hidden_1], stddev=0.1)),
    'conv2':  tf.Variable(tf.random_normal([ksize, ksize, num_hidden_1, num_hidden_2], stddev=0.1)),
    'conv3':  tf.Variable(tf.random_normal([ksize, ksize, num_hidden_2, num_hidden_3], stddev=0.1)),
    'conv4':  tf.Variable(tf.random_normal([ksize, ksize, num_hidden_3, num_hidden_4], stddev=0.1))
}
b_enc = {
    'conv1':  tf.Variable(tf.random_normal([num_hidden_1], stddev=0.1)),
    'conv2':  tf.Variable(tf.random_normal([num_hidden_2], stddev=0.1)),
    'conv3':  tf.Variable(tf.random_normal([num_hidden_3], stddev=0.1)),
    'conv4':  tf.Variable(tf.random_normal([num_hidden_4], stddev=0.1))
}

# Decoder
w_dec = {
    'tconv4': tf.Variable(tf.random_normal([ksize, ksize, num_hidden_3, num_hidden_4], stddev=0.1)),
    'tconv3': tf.Variable(tf.random_normal([ksize, ksize, num_hidden_2, num_hidden_3], stddev=0.1)),
    'tconv2': tf.Variable(tf.random_normal([ksize, ksize, num_hidden_1, num_hidden_2], stddev=0.1)),
    'tconv1': tf.Variable(tf.random_normal([ksize, ksize, 1, num_hidden_1], stddev=0.1))
}

b_dec = {
    'tconv4': tf.Variable(tf.random_normal([num_hidden_3], stddev=0.1)),
    'tconv3': tf.Variable(tf.random_normal([num_hidden_2], stddev=0.1)),
    'tconv2': tf.Variable(tf.random_normal([num_hidden_1], stddev=0.1)),
    'tconv1': tf.Variable(tf.random_normal([1], stddev=0.1))
}

# Artefact remover
w_arem = {
    'tconv4': tf.Variable(tf.random_normal([ksize, ksize, num_arem_3, num_arem_4], stddev=0.1)),
    'tconv3': tf.Variable(tf.random_normal([ksize, ksize, num_arem_2, num_arem_3], stddev=0.1)),
    'tconv2': tf.Variable(tf.random_normal([ksize, ksize, num_arem_1, num_arem_2+16], stddev=0.1)),
    'tconv1': tf.Variable(tf.random_normal([ksize, ksize, 1,          num_arem_1], stddev=0.1))
}

b_arem = {
    'tconv4': tf.Variable(tf.random_normal([num_arem_3], stddev=0.1)),
    'tconv3': tf.Variable(tf.random_normal([num_arem_2], stddev=0.1)),
    'tconv2': tf.Variable(tf.random_normal([num_arem_1], stddev=0.1)),
    'tconv1': tf.Variable(tf.random_normal([1], stddev=0.1))
}

# Saver
saver = tf.train.Saver()


load_filename = load_foldername+'/'+load_foldername.split("/")[-1]
save_filename = save_foldername+'/'+save_foldername.split("/")[-1]

print('[Welcome] ZAT AutoEncoder\n')
print('[info] Computation options')
print(' |- num epochs          = %i' % num_steps)
print(' |- training batch size = %i' % batch_size)
print(' |- testing batch size  = %i' % test_dataset_size)
print(' |- display every %i epochs' % display_steps)
if loading:
	print(' |- loading %s' % load_foldername)
else:
	print(' |- loading disabled')
if saving:
	print(' |- saving in %s' % save_foldername)
	while not os.path.isdir(save_foldername):
		mkdir = str(raw_input('[?] Create new folder "'+save_foldername+'" ? (Y/n) '))
		if mkdir.lower() == 'y' or mkdir == '':
			os.makedirs(save_foldername)
else:
	print(' |- saving disabled - sandbox mode')

print(' |- Computation time prediction = %s' % str(datetime.timedelta(seconds=round(batch_size*num_steps/65))))

mkdir = str(raw_input('[?] Parameters Ok ? (Y/n) '))
if mkdir.lower() != 'y' and mkdir.lower() != '':
	sys.exit()

# Building the encoder
def encoder(x, keep_prob):

	# Encoder Hidden layer with sigmoid activation #1
	layer_1 = tf.nn.sigmoid(tf.add(tf.nn.conv2d(x, w_enc['conv1'], strides=[1, 2, 2, 1], padding='SAME'), b_enc['conv1']))
	layer_1 = tf.nn.dropout(layer_1, keep_prob[0])
	#layer_1 = tf.nn.max_pool(layer_1, ksize=[1, 2, 2, 1], strides=[1, 2, 2, 1], padding='SAME')
	
	# Encoder Hidden layer with sigmoid activation #2
	layer_2 = tf.nn.sigmoid(tf.add(tf.nn.conv2d(layer_1, w_enc['conv2'], strides=[1, 2, 2, 1], padding='SAME'), b_enc['conv2']))
	layer_2 = tf.nn.dropout(layer_2, keep_prob[0])
	#layer_2 = tf.nn.max_pool(layer_2, ksize=[1, 2, 2, 1], strides=[1, 2, 2, 1], padding='SAME')
	#layer_2 = tf.reshape(layer_2, shape=[-1,w_enc['conv3'].get_shape().as_list()[0]])
	
	# Encoder Hidden layer with sigmoid activation #3
	layer_3 = tf.nn.sigmoid(tf.add(tf.nn.conv2d(layer_2, w_enc['conv3'], strides=[1, 2, 2, 1], padding='SAME'), b_enc['conv3']))
	layer_3 = tf.nn.dropout(layer_3, keep_prob[1])
	#layer_3 = tf.nn.max_pool(layer_3, ksize=[1, 1, 1, 1], strides=[1, 1, 1, 1], padding='SAME')

	layer_4 = tf.nn.sigmoid(tf.add(tf.nn.conv2d(layer_3, w_enc['conv4'], strides=[1, 2, 2, 1], padding='SAME'), b_enc['conv4']))
	layer_4 = tf.nn.dropout(layer_4, keep_prob[1])
	
	return layer_4, keep_prob




# Building the decoder
def decoder(x, keep_prob):

    # Decoder Hidden layer with sigmoid activation #4
	layer_4 = tf.nn.sigmoid(tf.add(tf.nn.conv2d_transpose(  x,
	                                                        w_dec['tconv4'],
	                                                        tf.stack([tf.shape(x)[0], 4, 4, num_hidden_3]),
	                                                        strides=[1, 2, 2, 1], padding='SAME'),
	                                                        b_dec['tconv4']))
	layer_4 = tf.nn.dropout(layer_4, keep_prob[1])
	
	# Decoder Hidden layer with sigmoid activation #3
	layer_3 = tf.nn.sigmoid(tf.add(tf.nn.conv2d_transpose(  layer_4,
	                                                        w_dec['tconv3'],
	                                                        tf.stack([tf.shape(x)[0], 7, 7, num_hidden_2]),
	                                                        strides=[1, 2, 2, 1], padding='SAME'),
	                                                        b_dec['tconv3']))
	layer_3 = tf.nn.dropout(layer_3, keep_prob[1])
	
	# Decoder Hidden layer with sigmoid activation #2
	layer_2 = tf.nn.sigmoid(tf.add(tf.nn.conv2d_transpose(  layer_3,
	                                                        w_dec['tconv2'],
	                                                        tf.stack([tf.shape(x)[0], 14, 14, num_hidden_1]),
	                                                        strides=[1, 2, 2, 1], padding='SAME'),
	                                                        b_dec['tconv2']))
	layer_2 = tf.nn.dropout(layer_2, keep_prob[0])
	
	# Decoder Hidden layer with sigmoid activation #1
	layer_1 = tf.nn.sigmoid(tf.add(tf.nn.conv2d_transpose(  layer_2,
	                                                        w_dec['tconv1'],
	                                                        tf.stack([tf.shape(x)[0], 28, 28, 1]),
	                                                        strides=[1, 2, 2, 1], padding='SAME'),
	                                                        b_dec['tconv1']))
	layer_1 = tf.nn.dropout(layer_1, keep_prob[0])

	#layer_0 = tf.nn.sigmoid(tf.add(tf.nn.conv2d(  layer_1, w_dec['conv0'], strides=[1, 2, 2, 1], padding='SAME'), b_dec['conv0']))
	#layer_0 = tf.nn.dropout(layer_0, keep_prob[1])
	
	return layer_1


def artefact_cleaner(x,x_compressed,keep_prob):
	
    # Decoder Hidden layer with sigmoid activation #4
	reshape_compressed_4 = tf.nn.sigmoid(tf.add(tf.nn.conv2d_transpose(  x_compressed,
	                                                                     w_arem['tconv4'],
	                                                                     tf.stack([tf.shape(x)[0], 4, 4, num_arem_3]),
	                                                                     strides=[1, 2, 2, 1], padding='SAME'),
	                                                                     b_arem['tconv4']))
	reshape_compressed_4 = tf.nn.dropout(reshape_compressed_4, keep_prob[1])

    # Decoder Hidden layer with sigmoid activation #4
	reshape_compressed_3 = tf.nn.sigmoid(tf.add(tf.nn.conv2d_transpose(  reshape_compressed_4,
	                                                                     w_arem['tconv3'],
	                                                                     tf.stack([tf.shape(x)[0], 7, 7, num_arem_2]),
	                                                                     strides=[1, 2, 2, 1], padding='SAME'),
	                                                                     b_arem['tconv3']))
	reshape_compressed_3 = tf.nn.dropout(reshape_compressed_3, keep_prob[0])

	x_spliced = tf.reshape( x, [-1,7,7,16])
	x_mix = tf.concat([reshape_compressed_3,x_spliced], 3)
	
	layer_2 = tf.nn.sigmoid(tf.add(tf.nn.conv2d_transpose(  x_mix,
	                                                        w_arem['tconv2'],
	                                                        tf.stack([tf.shape(x_mix)[0], 14, 14, num_arem_1]),
	                                                        strides=[1, 2, 2, 1], padding='SAME'),
	                                                        b_arem['tconv2']))
	layer_2 = tf.nn.dropout(layer_2, keep_prob[0])
	
	layer_1 = tf.nn.sigmoid(tf.add(tf.nn.conv2d_transpose(  layer_2,
	                                                        w_arem['tconv1'],
	                                                        tf.stack([tf.shape(x_mix)[0], 28, 28, 1]),
	                                                        strides=[1, 2, 2, 1], padding='SAME'),
	                                                        b_arem['tconv1']))
	layer_1 = tf.nn.dropout(layer_1, keep_prob[1])
	
	return layer_1


# Construct model
encoder_op,keep_prob = encoder(X, keep_prob)
decoder_op = decoder(encoder_op,keep_prob)
decoder_op_sta = decoder(tf.reshape(Y,[-1,2,2,num_hidden_4]),keep_prob)

arem_op = artefact_cleaner(X,encoder_op,keep_prob)

# Prediction
y_pred = decoder_op
y_pred_arem = arem_op
# Targets (Labels) are the input data.
y_true = X

# Define loss and optimizer, minimize the squared error
loss = tf.reduce_sum(tf.pow(tf.reshape(y_true, [-1,28,28,1]) - y_pred, 2))
loss_arem = tf.reduce_sum(tf.pow(tf.reshape(y_true, [-1,28,28,1]) - y_pred_arem, 2))
#optimizer = tf.train.RMSPropOptimizer(learning_rate).minimize(loss)
optimizer = tf.train.AdamOptimizer(learning_rate).minimize(loss)
optimizer_arem = tf.train.AdamOptimizer(learning_rate).minimize(loss_arem)


# Initialize GUI monitoring
mean_img = np.zeros((784))
plt.ion()
grid = plt.GridSpec(4,8, wspace=0.1, hspace=0.2)
fig	 = plt.figure(figsize=(3,8))
axs_lmon = fig.add_subplot(grid[2:,:3])
axs_hpmon = fig.add_subplot(grid[1,:3])
txt_mon = fig.add_subplot(grid[0,:3])

axs = list()
for x in range(0,4):
	axs.append(list())
	for y in range(3,8):
		axs[x].append(fig.add_subplot(grid[x,y]))


# Initialize the variables (i.e. assign their default value)
init = tf.global_variables_initializer()


# Start a new TF session
with tf.Session() as sess:

	# Run the initializer
	sess.run(init)
	
	# Load session
	if loading:
		saver.restore(sess,load_filename+'.wb')

	loss_graph = list()
	loss_graph_arem = list()
	test_graph = list()
	test_graph_arem = list()
	test_index = list()
	kpl3_graph = list()
	mon_gif = list()
	l_arem = 0
	l_test_arem = 0
	l_dec = -1

	i_file = 0
	if os.path.exists(load_filename+'.pkl') and loading:
		pickle_file = open(load_filename+'.pkl',"rb")
		i_file, loss_graph, l_dec, loss_graph_arem, l_arem, test_graph, test_graph_arem, test_index, kpl3_graph, mon_gif =  pickle.load(pickle_file)
		pickle_file.close()
		if i_file>=num_steps:
			num_steps += i_file
	
	
	# Training
	duration_training = 0
	# Prepare Data
	# Get the next batch of MNIST data (only images are needed, not labels)
	batch_train = mnist_data[0][0][:batch_size]
	batch_train = batch_train[:].reshape(batch_size,28,28,1)
	batch_train = batch_train[:]/255.
	for i in range(i_file, num_steps):

		time_start_batch = time.clock()

		if i!=0 and loss_graph[-1]<100:
			kp3 = kp*(1-((loss_graph[-1])/200))
			#kp3 = kp
		else:
			kp3 = kp*0.5

		# Run optimization op (backprop) and cost op (to get loss value)
		if training:
			if (l_dec/batch_size)>15 or l_dec == -1:
				_, l_dec = sess.run([optimizer, loss], feed_dict={X: batch_train, keep_prob: [kp,kp3]})
			if (l_dec/batch_size)<20:
				_, l_arem = sess.run([optimizer_arem, loss_arem], feed_dict={X: batch_train, keep_prob: [kp,kp3]})
		else:
			l_dec = sess.run(loss, feed_dict={X: batch_train, keep_prob: [1,1]})
		
		loss_graph_arem.append(l_arem/batch_size)
		loss_graph.append(l_dec/batch_size)
		kpl3_graph.append(kp3)

		time_end_training = time.clock()
		duration_training += time_end_training-time_start_batch
		
		# Testing
		if (i % display_steps) == 0:
			batch_x = mnist_data[1][0][:test_dataset_size]
			batch_x = batch_x[:].reshape(test_dataset_size,28,28,1)
			batch_x = batch_x[:]/255.
			l_test = sess.run(loss, feed_dict={X: batch_x, keep_prob: [1,1]})
			if (l_dec/batch_size)<20:
				l_test_arem = sess.run(loss_arem, feed_dict={X: batch_x, keep_prob: [1,1]})
			test_index.append(i)
			test_graph.append(l_test/test_dataset_size)
			test_graph_arem.append(l_test_arem/test_dataset_size)
			
			# Display logs per step
			print('[~] Step %i: Minibatch Loss: %f' % (i, l_dec/batch_size), end='\r')
			sys.stdout.flush()

			n_examples = 5
			batch_x = mnist_data[0][0][:n_examples]
			batch_x = batch_x[:].reshape(n_examples,28,28,1)
			batch_x = batch_x[:]/255.

			recon = sess.run(y_pred, feed_dict={X: batch_x, keep_prob: [1,1]})
			compressed = sess.run(encoder_op,feed_dict={X: batch_x, keep_prob: [1,1]})
			compressed = np.reshape(compressed, [-1,8,8,1])
			cleaned = sess.run(arem_op,feed_dict={X: batch_x, keep_prob: [1,1]})

			axs_lmon.clear()
			axs_lmon.set_xlim([10,num_steps])
			axs_lmon.plot(loss_graph, label='encoder training error')
			axs_lmon.plot(loss_graph_arem, label='art.rem training error')
			axs_lmon.plot(test_index,test_graph, label='encoder testing error')
			axs_lmon.plot(test_index,test_graph_arem, label='art.rem testing error')
			axs_lmon.legend()

			axs_hpmon.clear()
			axs_hpmon.set_xlim([10,num_steps])
			axs_hpmon.plot(kpl3_graph, label='keep_prob l3')
			axs_hpmon.legend()

			for example_i in range(n_examples):
				axs[0][example_i].matshow(np.reshape(batch_x[example_i, :], (28, 28)), cmap=plt.get_cmap('gray'))
				axs[1][example_i].matshow(compressed[example_i,:,:,0], cmap=plt.get_cmap('hot'))
				axs[2][example_i].matshow(np.reshape(np.reshape(recon[example_i, ...], (784,))+ mean_img, (28, 28)), cmap=plt.get_cmap('gray'))
				axs[3][example_i].matshow(np.reshape(np.reshape(cleaned[example_i, ...], (784,))+ mean_img, (28, 28)), cmap=plt.get_cmap('gray'))
				axs[0][example_i].axis('off')
				axs[1][example_i].axis('off')
				axs[2][example_i].axis('off')
				axs[3][example_i].axis('off')

			time_end_testing = time.clock()

			duration_testing = time_end_testing-time_end_training

			# Text monitor
			txt_mon.clear()
			txt_mon_epoch =  'Epoch         : '+str(i)+'/'+str(num_steps)
			txt_mon_trainl = 'Training loss : '+str(round(l_dec/batch_size,1)) +' (dec)   '+str(round(l_arem/batch_size,1))+' (arem)'
			txt_mon_testl =  'Testing loss  : '+str(round(l_test/test_dataset_size,1))+' (dec)   '+str(round(l_test_arem/test_dataset_size,1))+' (arem)'
			txt_mon_duration =  'Duration : '+str(round(duration_training,1)) \
							+'s - '+str(round(duration_training*100/(duration_testing+duration_training),1))+'% (train)    ' \
							+str(round(duration_testing,1))+'s - '+str(round(duration_testing*100/(duration_testing+duration_training),1))+'% (test)'
			txt_mon_rate =      'Rate :     '+str(round(batch_size*display_steps/duration_training)) + ' /sec (train)    ' \
							+str(round(test_dataset_size*display_steps/duration_testing)) + ' /sec (test)'
			txt_mon_disp = txt_mon_epoch+'\n\n'+txt_mon_trainl+'\n'+txt_mon_testl+'\n\n'+txt_mon_duration+'\n'+txt_mon_rate
			txt_mon.text(0.0, 1.0, txt_mon_disp, horizontalalignment='left', verticalalignment='top', transform=txt_mon.transAxes)
			txt_mon.axis('off')
			fig.canvas.draw()

			image = np.frombuffer(fig.canvas.tostring_rgb(), dtype='uint8')
			image = image.reshape(fig.canvas.get_width_height()[::-1] + (3,))
			mon_gif.append(image)

			if training and saving:
				imageio.mimsave(save_filename+'.gif', mon_gif, fps=4)
				save_path = saver.save(sess, save_filename+'.wb')
				call(('ffmpeg -y -v quiet -i '+save_filename+'.gif -q 0 '+save_filename+'.avi').split(" "))
				pickle_file = open(save_filename+'.pkl',"wb")
				pickle.dump([i+1, loss_graph, l_dec, loss_graph_arem, l_arem, test_graph, test_graph_arem, test_index, kpl3_graph, mon_gif], pickle_file)
				pickle_file.close()

			with open("./data/run_file.txt","r+") as f:
				if f.read() == 'abort\n':
					f.truncate(0)
					f.close()
					sys.exit()
				f.close()

			duration_testing = time.clock()-time_end_testing
			duration_training = 0
		
	

	# Testing
	loss_dict = {}
	for i in range(0,10000):
		batch_x = mnist_data[1][0][i]
		batch_x = batch_x[:].reshape(1,28,28,1)
		batch_x = batch_x[:]/255.
		l = sess.run(loss_arem, feed_dict={X: batch_x, keep_prob: [1,1]})
		loss_dict[i] = l
		
		if (i%25)==0:
			print('Testing %i/10000 - %f' %(i,round(i/100,1)))
	
	loss_dict = sorted(loss_dict.items(), key=operator.itemgetter(1))
	fig_test_mon, axs_test_mon = plt.subplots(4, 8, figsize=(15, 4))
	for i in range(-8,0):
		print('Showing %i : loss=%f' %(loss_dict[i][0],loss_dict[i][1]))
		batch_x = mnist_data[0][0][loss_dict[i][0]]
		batch_x = batch_x[:].reshape(1,28,28,1)
		batch_x = batch_x[:]/255.
		l,compressed,recon,cleaned = sess.run([loss,encoder_op,decoder_op,arem_op], feed_dict={X: batch_x, keep_prob: [1,1]})
		axs_test_mon[0][i].matshow(np.reshape(batch_x[0, :], (28, 28)), cmap=plt.get_cmap('gray'))
		axs_test_mon[1][i].matshow(compressed[0,:,:,0], cmap=plt.get_cmap('hot'))
		axs_test_mon[2][i].matshow(np.reshape(np.reshape(recon[0, ...], (784,))+ mean_img, (28, 28)), cmap=plt.get_cmap('gray'))
		axs_test_mon[3][i].matshow(np.reshape(np.reshape(cleaned[0, ...], (784,))+ mean_img, (28, 28)), cmap=plt.get_cmap('gray'))
		axs_test_mon[0][i].axis('off')
		axs_test_mon[1][i].axis('off')
		axs_test_mon[2][i].axis('off')
		axs_test_mon[3][i].axis('off')
	fig_test_mon.canvas.draw()

	
	
	#fig_test, axs_test = plt.subplots(2, 1, figsize=(15, 4))
	#old_im = 0
	#in_test = True
	#while in_test:
	#    im = Image.open("compressed_test.bmp")
	#    if im != old_im:
	#        test = np.array(im)
	#        test = test[:,:,0]/255.
	#        test = np.reshape(test, [1,8,8,1])
	#        decoded = sess.run(decoder_op_sta, feed_dict={Y: test, keep_prob: 1})
	
	#        axs_test[0].matshow(test[0,:,:,0], cmap=plt.get_cmap('gray'))
	#        axs_test[1].matshow(decoded[0,:,:,0], cmap=plt.get_cmap('gray'))
	#        fig_test.canvas.draw()
	#        old_im = im
	#    else:
	#        time.sleep(2)


