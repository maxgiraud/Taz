
# Saver
saver = tf.train.Saver()


load_filename = load_foldername+'/'+load_foldername.split("/")[-1]
save_filename = save_foldername+'/'+save_foldername.split("/")[-1]

if not os.path.isdir(save_foldername) and save_foldername!='':
	os.makedirs(save_foldername)


# Initialize GUI monitoring
mean_img = np.zeros((784))
#plt.ion()
grid = plt.GridSpec(4,5, wspace=0.1, hspace=0.1)
#fig	 = plt.figure(figsize=(3,8),frameon=False)
fig	 = plt.figure(figsize=(6,4),frameon=False,dpi=300)

grid2 = plt.GridSpec(4,2, wspace=0.1, hspace=0.1)
fig2	 = plt.figure(figsize=(6,4),frameon=False,dpi=300)
axs_lmon = fig2.add_subplot(grid2[2:,:])
axs_hpmon = fig2.add_subplot(grid2[1,:])
txt_mon = fig2.add_subplot(grid2[0,:])

axs = list()
for x in range(0,4):
	axs.append(list())
	for y in range(0,5):
		axs[x].append(fig.add_subplot(grid[x,y]))

plt.rcParams.update({'font.size': 6})

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
	#mon_gif = list()
	l_arem = 0
	l_test_arem = 0
	l_dec = -1

	i_file = 0
	if os.path.exists(load_filename+'.pkl') and loading:
		pickle_file = open(load_filename+'.pkl',"rb")
		#i_file, loss_graph, l_dec, loss_graph_arem, l_arem, test_graph, test_graph_arem, test_index, kpl3_graph, mon_gif =  pickle.load(pickle_file)
		i_file, loss_graph, l_dec, loss_graph_arem, l_arem, test_graph, test_graph_arem, test_index, kpl3_graph =  pickle.load(pickle_file)
		pickle_file.close()

	num_packet = 0
	abort = False	
	#ofile = open("/home/max/python/tensorflow/autoencoder/data/io/run_ofile.txt","w")
	#ifile = open("/home/max/python/tensorflow/autoencoder/data/io/run_ifile.txt","r+")
	ofile = open(ofile_path,"w")
	ifile = open(ifile_path,"r+")
	
	ofile.write(str(num_packet)+'\ntraining_begin dumb ')
	ofile.flush()
	num_packet+=1
	#time.sleep(10)
	
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
			if (l_dec/batch_size)>0 or l_dec == -1:
				_, l_dec = sess.run([optimizer, loss], feed_dict={X: batch_train, keep_prob: [kp,kp3]})
			if (l_dec/batch_size)<0:
				_, l_arem = sess.run([optimizer_arem, loss_arem], feed_dict={X: batch_train, keep_prob: [kp,kp3]})
		else:
			l_dec = sess.run(loss, feed_dict={X: batch_train, keep_prob: [1,1]})
		
		loss_graph_arem.append(l_arem/batch_size)
		loss_graph.append(l_dec/batch_size)
		kpl3_graph.append(kp3)

		time_end_training = time.clock()
		duration_training += time_end_training-time_start_batch
		
		# Testing
		if ((i+1) % display_steps) == 0:
			batch_x = mnist_data[1][0][:test_dataset_size]
			batch_x = batch_x[:].reshape(test_dataset_size,28,28,1)
			batch_x = batch_x[:]/255.
			l_test = sess.run(loss, feed_dict={X: batch_x, keep_prob: [1,1]})
			if (l_dec/batch_size)<0:
				l_test_arem = sess.run(loss_arem, feed_dict={X: batch_x, keep_prob: [1,1]})
			test_index.append(i+1)
			test_graph.append(l_test/test_dataset_size)
			test_graph_arem.append(l_test_arem/test_dataset_size)
			
			# Display logs per step
			print('[~] Step %i: Minibatch Loss: %f' % (i+1, l_dec/batch_size))
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
			txt_mon_epoch =  'Epoch         : '+str(i+1)+'/'+str(num_steps)
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
			#fig.canvas.draw()
			#plt.savefig('/home/max/python/tensorflow/autoencoder/data/temp/instants/instant_'+str(i+1)+'.jpeg')
			fig.savefig(instants_path+str(i+1)+'.png')
			fig2.savefig(instants_path+str(i+1)+'_2.png')
			
			#image = np.frombuffer(fig.canvas.tostring_rgb(), dtype='uint8')
			#image = image.reshape(autoframe(image.size/3) + (3,))
			#mon_gif.append(image)

			if training and saving:
				#imageio.mimsave(save_filename+'.gif', mon_gif, fps=4)
				save_path = saver.save(sess, save_filename+'.wb')
				#call(('ffmpeg -y -v quiet -i '+save_filename+'.gif -q 0 '+save_filename+'.avi').split(" "))
				pickle_file = open(save_filename+'.pkl',"wb")
				#pickle.dump([i+1, loss_graph, l_dec, loss_graph_arem, l_arem, test_graph, test_graph_arem, test_index, kpl3_graph, mon_gif], pickle_file)
				pickle.dump([i+1, loss_graph, l_dec, loss_graph_arem, l_arem, test_graph, test_graph_arem, test_index, kpl3_graph], pickle_file)
				pickle_file.close()
	
			#with open("/home/max/python/tensorflow/autoencoder/data/io/run_ifile.txt","r+") as ifile:
			if ifile.read() == 'abort\n':
				ifile.truncate(0)
				abort = True
				ifile.close()

			#with open("/home/max/python/tensorflow/autoencoder/data/io/run_ofile.txt","w") as ofile:
			ofile.seek(0)
			ofile.truncate()
			ofile.write(str(num_packet)+'\nepoch '+str(i+1)+'\n' \
                        #+'screen_log '+'/home/max/python/tensorflow/autoencoder/data/temp/instants/instant_'+str(i+1)+'.jpeg\n' \
                        +'screen_log '+instants_path+str(i+1)+'.png\n' \
                        +'monitoring 0 "Training loss" "'+str(round(l_dec/batch_size,1)) +'"\n' \
                        +'monitoring 1 "Testing loss" "'+str(round(l_test/test_dataset_size,1))+'"\n' \
                        +'monitoring 2 "Training duration" "'+str(round(duration_training,1)) \
                        +'s ('+str(round(duration_training*100/(duration_testing+duration_training),1))+'%)"\n' \
                        +'monitoring 3 "Testing duration" "'+str(round(duration_testing,1)) \
                        +'s ('+str(round(duration_testing*100/(duration_testing+duration_training),1))+'%)"\n'
                        +'monitoring 4 "Training rate" "'+str(round(batch_size*display_steps/duration_training)) + ' /sec"\n' \
                        +'monitoring 5 "Testing rate" "'+str(round(test_dataset_size*display_steps/duration_testing)) + ' /sec"\n')
			ofile.flush()
			num_packet+=1
			#ofile.close()

			if abort:
				break

			duration_testing = time.clock()-time_end_testing
			duration_training = 0
	
	time.sleep(1)
	ofile.seek(0)
	ofile.truncate()
	ofile.write(str(num_packet)+' training_done dumb\n')
	ofile.flush()
	num_packet+=1
	time.sleep(1)
		
	## Testing
	if not abort:
		ofile.seek(0)
		ofile.truncate(0)
		ofile.write(str(num_packet)+' testing_begin dumb\n')
		ofile.flush()
		num_packet+=1
		time.sleep(1)
		#loss_dict = {}
		#for i in range(0,10000):
		#	batch_x = mnist_data[1][0][i]
		#	batch_x = batch_x[:].reshape(1,28,28,1)
		#	batch_x = batch_x[:]/255.
		#	l = sess.run(loss_arem, feed_dict={X: batch_x, keep_prob: [1,1]})
		#	loss_dict[i] = l
		#	
		#	if (i%25)==0:
		#		print('Testing %i/10000 - %f' %(i,round(i/100,1)))
		#
		#loss_dict = sorted(loss_dict.items(), key=operator.itemgetter(1))
		#fig_test_mon, axs_test_mon = plt.subplots(4, 8, figsize=(15, 4))
		#for i in range(-8,0):
		#	print('Showing %i : loss=%f' %(loss_dict[i][0],loss_dict[i][1]))
		#	batch_x = mnist_data[0][0][loss_dict[i][0]]
		#	batch_x = batch_x[:].reshape(1,28,28,1)
		#	batch_x = batch_x[:]/255.
		#	l,compressed,recon,cleaned = sess.run([loss,encoder_op,decoder_op,arem_op], feed_dict={X: batch_x, keep_prob: [1,1]})
		#	axs_test_mon[0][i].matshow(np.reshape(batch_x[0, :], (28, 28)), cmap=plt.get_cmap('gray'))
		#	axs_test_mon[1][i].matshow(compressed[0,:,:,0], cmap=plt.get_cmap('hot'))
		#	axs_test_mon[2][i].matshow(np.reshape(np.reshape(recon[0, ...], (784,))+ mean_img, (28, 28)), cmap=plt.get_cmap('gray'))
		#	axs_test_mon[3][i].matshow(np.reshape(np.reshape(cleaned[0, ...], (784,))+ mean_img, (28, 28)), cmap=plt.get_cmap('gray'))
		#	axs_test_mon[0][i].axis('off')
		#	axs_test_mon[1][i].axis('off')
		#	axs_test_mon[2][i].axis('off')
		#	axs_test_mon[3][i].axis('off')
		#fig_test_mon.canvas.draw()
	
		ofile.seek(0)
		ofile.truncate()
		ofile.write(str(num_packet)+' testing_done dumb\n')
		ofile.flush()
		num_packet+=1
	time.sleep(1)
	
	#ofile.truncate(0)
	ofile.seek(0)
	ofile.truncate()
	ofile.write(str(num_packet)+' finish dumb\n')
	#ofile.flush()
	num_packet+=1
	ofile.close()
	
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

	#while True:
	#	time.sleep(3)
	#with open("/home/max/python/tensorflow/autoencoder/data/io/run_ifile.txt","r+") as f:
	#	if f.read() == 'abort\n':
	#		f.truncate(0)
	#		f.close()
	#		sys.exit()
	#	f.close()

