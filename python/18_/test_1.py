# -*- coding: utf-8 -*-
'''
pushd C:\WORKS_2\WS\Eclipse_Luna\C_SoundProg\python\18_\
test_1.py

ref : http://aidiary.hatenablog.com/entry/20110607/1307449007

'''
###############################################
import sys
from sympy.solvers.tests.test_constantsimp import C2
sys.path.append('.')
sys.path.append('..')
from libs.libs import *		#=> C:\WORKS_2\WS\Eclipse_Luna\C_SoundProg\python\libs
# import libs.libs as lib
# from libs.libs import *		#=> in 'libs' subdirectory --> see : https://stackoverflow.com/questions/1260792/import-a-file-from-a-subdirectory 'community wiki'
    						#=> ref : http://qiita.com/Usek/items/86edfa0835292c80fff5
# from libs import *		#=> in 'libs' subdirectory --> see : https://stackoverflow.com/questions/1260792/import-a-file-from-a-subdirectory 'community wiki'
    					#=> libs.py : C:\WORKS_2\WS\WS_Others\free\K6H7DD_schroedinger\28_1\libs.py

import libs.labs2 as labs
# import libs.labs as labs

import libs.wablibs as wl
# import wablibs
# import wablibs as wl

import getopt
import os
import inspect

import math as math

###############################################
import wave
import struct
import numpy as np
from pylab import *

from matplotlib import pylab as plt

import random as rnd

def show_Message() :
    			
    msg = '''
    <Options>
    -v	Volume down the amplitude --> 1.0 * v / 1000
    -f	Base frequency ---> e.g. 262 for the A tone
    -p	Phase of the sine curves ---> sin(2 * np.pi * f0 * n * phase / fs)'''
    
    print msg

def exec_prog() :
    
    print "[%s:%d] exec_prog" % (thisfile(), linenum())
    
    a = 1     #振幅
    fs = 8000 #サンプリング周波数
    f0 = 440  #周波数
    sec = 5   #秒
     
    swav=[]
    
    pow_Val = 2
    
    for n in np.arange(fs * sec):
        #サイン波を生成
        s = a * np.power(np.sin(2.0 * np.pi * f0 * n / fs), pow_Val) \
            * np.cos(2.0 * np.pi * f0 * n / fs) * (-1)
#         s = a * np.sin(2.0 * np.pi * f0 * n / fs) \
#             * np.cos(2.0 * np.pi * f0 * n / fs)
#         s = a * np.power(np.sin(2.0 * np.pi * f0 * n / fs), pow_Val)
#         s = a * np.sin(2.0 * np.pi * f0 * n / fs)
        swav.append(s)
        
#     plt.plot(swav[0:100])
#     plt.show()
    
    #サイン波を-32768から32767の整数値に変換(signed 16bit pcmへ)
    swav = [int(x * 32767.0) for x in swav]
     
    #バイナリ化
    binwave = struct.pack("h" * len(swav), *swav)
     
    #サイン波をwavファイルとして書き出し
    fname_Out = "output_%s.sin-pow-2_cos_(-1).wav" % (get_TimeLabel_Now())
#     fname_Out = "output_%s.pow-%d.wav" % (get_TimeLabel_Now(), pow_Val)
    
    w = wave.Wave_write(fname_Out)
#     w = wave.Wave_write("output.wav")
    p = (1, 2, 8000, len(binwave), 'NONE', 'not compressed')
    w.setparams(p)
    w.writeframes(binwave)
    w.close()

'''
<usage>
test_1.py [-fXXX]  #=> frequency
test_1.py -f402
'''
if __name__ == "__main__" :

    '''###################
    	validate : help option		
    ###################'''

    '''###################
    	get options		
    ###################'''

    '''###################
    	evecute		
    ###################'''
    exec_prog()

    print
    print "[%s:%d] done" % (thisfile(), linenum())
