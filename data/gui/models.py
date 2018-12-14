import tensorflow as tf

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

learning_rate = 0.001

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
