# -*- coding: utf-8 -*-
'''
pushd C:\WORKS_2\WS\Eclipse_Luna\C_SoundProg\python\16_1
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

import libs.labs as labs

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

import random as rnd

def show_Message() :
    			
    msg = '''
    <Options>
    -v	Volume down the amplitude --> 1.0 * v / 1000
    -f	Base frequency ---> e.g. 262 for the A tone
    -p	Phase of the sine curves ---> sin(2 * np.pi * f0 * n * phase / fs)'''
    
    print msg

'''
<usage>
test_1.py [-fXXX]  #=> frequency
test_1.py -f402
'''
def exec_1__SinePlusCosine_Standardize():
    
    '''###################
    	options		
    ###################'''
    options = get_opt_2(sys.argv, "f")
    
    if not "-f" in [x[0] for x in options] :
    	
    	print "'-f' option needed"
    	
    	return
    
#     print options
#      
#     return
    
    '''###################
    	prep : wfs		
    ###################'''
    '''###################
    	prep : wfs : sines
    ###################'''
    A = 1.0; fs = 8000.0; length = 1.0; phase = 1.0; type = "sine"
    
    f0_val = [x[1] for x in options if x[0] == '-f'][0]
    
    f0 = int(f0_val);
#     f0 = 262 * wl.EQUAL_TEMPERAMENTS[6];
#     f0 = 262 * wl.EQUAL_TEMPERAMENTS[3];
#     f0 = 262;
    
    timelabel = get_TimeLabel_Now()
    
    fname_Sines = "test_1.sines.%s.f0=%d_phase-%1.2f.wav" % (timelabel, f0, phase)
    
    wf_Sines = wl.get_WaveFile__Sines (fname_Sines, A, f0, fs, length, phase, type)

    '''###################
    	prep : wfs : cosines
    ###################'''
    A = 1.0; fs = 8000.0; length = 1.0; phase = 1.0; type = "cosine"
    
    f0_val = [x[1] for x in options if x[0] == '-f'][0]
    
    f0 = int(f0_val);
#     f0 = 262 * wl.EQUAL_TEMPERAMENTS[6];
#     f0 = 262 * wl.EQUAL_TEMPERAMENTS[3];
#     f0 = 262;
    
    timelabel = get_TimeLabel_Now()
    
    fname_Cosines = "test_1.cosines.%s.f0=%d_phase-%1.2f.wav" % (timelabel, f0, phase)
    
    wf_Cosines = wl.get_WaveFile__Sines (fname_Cosines, A, f0, fs, length, phase, type)

    '''###################
        prep : wfs : sines + cosines
    ###################'''
    pairsOf_analogdata = zip(wf_Sines.analogdata, wf_Cosines.analogdata)
    
    analogdata_Stardardized = [1/sqrt(2) * (x + y) for x, y in pairsOf_analogdata]
    
    print "[%s:%d] analogdata_Stardardized : max = %.4f / min = %.4f" \
                % (thisfile(), linenum(), \
                   max(analogdata_Stardardized), \
                   min(analogdata_Stardardized))
    	
    
    fname_SinesPlusCosines = "test_1.SinesPlusCosines.%s.wav" % (timelabel)
    
    wf_SinesPlusCosines = wl.get_WaveFile__AnalogData(\
                fname = fname_SinesPlusCosines, \
                analogdata = analogdata_Stardardized, \
                A = 1.0, length = wf_Sines.length,\
                radians = wf_Sines.radians, \
                f0 = wf_Sines.basefreq)
#                 A, length, nchannels = 1, \

    '''###################
    	measure freq		
    ###################'''
    result_Sines = wl.measure_Frequency_4(wf_Sines)
    
    result_Cosines = wl.measure_Frequency_4(wf_Cosines)
    
    result_SinesPlusCosines = wl.measure_Frequency_4(wf_SinesPlusCosines)
    
    print "[%s:%d] freq of sines ==> %d" % (thisfile(), linenum(), result_Sines['freq'])
#     print "[%s:%d] freq of sines ==> %d" % (thisfile(), linenum(), result_Sines)
    
    print "[%s:%d] freq of cosines ==> %d" % (thisfile(), linenum(), result_Cosines['freq'])
#     print "[%s:%d] freq of cosines ==> %d" % (thisfile(), linenum(), result_Cosines)
    
    print "[%s:%d] result_Sines =>" % (thisfile(), linenum())
    
    print result_Sines
    
    print "[%s:%d] result_Cosines =>" % (thisfile(), linenum())
    
    print result_Cosines
    
    print "[%s:%d] result_SinesPlusCosines =>" % (thisfile(), linenum())
    
    print result_SinesPlusCosines
    
    '''###################
        save to file        
    ###################'''
    # sines
    dpath = "audio"
    
    wl.save_WaveFile__Class(wf_Sines, dpath_dst=dpath)
    
    # cosines
    wl.save_WaveFile__Class(wf_Cosines, dpath_dst=dpath)
    
    # sines + cosines
    wl.save_WaveFile__Class(wf_SinesPlusCosines, dpath_dst=dpath)
    
    print "[%s:%d] files saved" % (thisfile(), linenum())
                
    
    '''###################
    	ending		
    ###################'''
    print "[%s:%d] exec_1__Measure_Frequency ==> done" % (thisfile(), linenum())
    		
    
    '''###################
    	return		
    ###################'''
    return

if __name__ == "__main__" :

    '''###################
    	validate : help option		
    ###################'''
    args = sys.argv
    
    if '-h' in args or '-help' in args : 
    	show_Message()
    	
    	sys.exit(1)

    '''###################
    	get options		
    ###################'''
    keychars = "vf"
    
    result = get_opt_2(sys.argv, keychars)

    '''###################
    	evecute		
    ###################'''
    exec_1__SinePlusCosine_Standardize()
    
    print
    print "[%s:%d] done" % (thisfile(), linenum())
