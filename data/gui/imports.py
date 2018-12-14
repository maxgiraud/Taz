#!/usr/bin/python3.6

from __future__ import division, print_function, absolute_import

import tensorflow as tf
import numpy as np
from PIL import Image
import matplotlib.pyplot as plt
import math
import sys
import time
import operator
from keras.datasets import mnist
import pickle
import imageio
from subprocess import call
import os
import datetime

from tools import autoframe
from models import *

#import MNIST data
mnist_data = mnist.load_data()

