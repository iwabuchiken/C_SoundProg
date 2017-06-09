###############################################
import sys
from scipy.signal.windows import cosine
sys.path.append('.')
from libs import *

import getopt
import os
import inspect
###############################################
import wave
import struct
import numpy as np
from pylab import *
from matplotlib import pylab as plt

import random as rnd


def test_Max_InThe_List():
    
    #ref arange https://stackoverflow.com/questions/477486/how-to-use-a-decimal-range-step-value 'answered Jan 25 '09 at 12:26'
    sines = [sin(x) for x in np.arange(-np.pi, np.pi, np.pi / 360)]
    
    cosines = [cos(x) for x in np.arange(-np.pi, np.pi, np.pi / 360)]
    
    #ref zip https://stackoverflow.com/questions/18713321/element-wise-addition-of-2-lists 'answered Sep 10 '13 at 7:50'
    sines_cosines = [sum(x) for x in zip(sines, cosines)]
    
    sines_times_cosines = [x * y for x, y in zip(sines, cosines)]
    
    #ref max https://www.tutorialspoint.com/python/list_max.htm
    max_val = max(sines)
    
    print "[%s:%d] max(sines) => %f" % (thisfile(), linenum(), max_val)
    
    print "[%s:%d] max(sines_cosines) => %f" % (thisfile(), linenum(), max(sines_cosines))
    
    print "[%s:%d] max(sines_times_cosines) => %f" % (thisfile(), linenum(), max(sines_times_cosines))

def test_Addition_Sine_and_Sine():
    
    a = 1
    
    sines_1 = [sin(x) for x in np.arange(-np.pi, np.pi, np.pi / 360)]
    sines_2 = [sin(x + a) for x in np.arange(-np.pi, np.pi, np.pi / 360)]
    
    sines_sum = [sum(x) for x in zip(sines_1, sines_2)]
    
    print "[%s:%d] max(sines_sum) => %f" % (thisfile(), linenum(), max(sines_sum))
    print "[%s:%d] min(sines_sum) => %f" % (thisfile(), linenum(), min(sines_sum))
    
    
#     plt.plot(sines_sum)
#     
#     #ref http://qiita.com/irs/items/cd1556c568887ff2bdd7
#     plt.grid(which='major',color='black',linestyle='-')
#     plt.grid(which='minor',color='black',linestyle='-')
# 
#     plt.show()
    

if __name__ == "__main__" :
    
#     test_Max_InThe_List()
    test_Addition_Sine_and_Sine()