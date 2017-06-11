# -*- coding: utf-8 -*-
'''
pushd C:\WORKS_2\WS\Eclipse_Luna\C_SoundProg\python\15_1
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

def exec_1__Measure_Frequency():
    
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
    A = 1.0; fs = 8000.0; length = 1.0; phase = 1.0; type = "sine"
    
    f0_val = [x[1] for x in options if x[0] == '-f'][0]
    
    f0 = int(f0_val);
#     f0 = 262 * wl.EQUAL_TEMPERAMENTS[6];
#     f0 = 262 * wl.EQUAL_TEMPERAMENTS[3];
#     f0 = 262;
    
    timelabel = get_TimeLabel_Now()
    
    fname_sines = "test_1.sines.%s.f0=%d_phase-%1.2f.wav" % (timelabel, f0, phase)
    
    wf_sines = wl.get_WaveFile__Sines (fname_sines, A, f0, fs, length, phase, type)

    '''###################
    	measure freq		
    ###################'''
    result = wl.measure_Frequency_2(wf_sines)
#     result = wl.measure_Frequency(wf_sines)
    
    
    '''###################
    	ending		
    ###################'''
    print "[%s:%d] exec_1__Measure_Frequency ==> done" % (thisfile(), linenum())
    		
    
    '''###################
    	return		
    ###################'''
    return

def exec_2__Measure_Frequency_Others():
    
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
    	prep : wf : sine
    ###################'''
    A = 1.0; fs = 8000.0; length = 1.0; phase = 1.0; type = "sine"
    
    f0_val = [x[1] for x in options if x[0] == '-f'][0]
    
    f0 = int(f0_val);
#     f0 = 262 * wl.EQUAL_TEMPERAMENTS[6];
#     f0 = 262 * wl.EQUAL_TEMPERAMENTS[3];
#     f0 = 262;
    
    timelabel = get_TimeLabel_Now()
    
    fname_sines = "test_1.sines.%s.f0=%d_phase-%1.2f.wav" % (timelabel, f0, phase)
    
    wf_sines = wl.get_WaveFile__Sines (fname_sines, A, f0, fs, length, phase, type)

    '''###################
    	prep : wf : cosine
    ###################'''
    A = 1.0; fs = 8000.0; length = 1.0; phase = 1.0; type = "cosine"
    
    f0_val = [x[1] for x in options if x[0] == '-f'][0]
    
    f0 = int(f0_val);
#     f0 = 262 * wl.EQUAL_TEMPERAMENTS[6];
#     f0 = 262 * wl.EQUAL_TEMPERAMENTS[3];
#     f0 = 262;
    
    timelabel = get_TimeLabel_Now()
    
    fname_cosines = "test_1.cosines.%s.f0=%d_phase-%1.2f.wav" % (timelabel, f0, phase)
    
    wf_cosines = wl.get_WaveFile__Sines (fname_cosines, A, f0, fs, length, phase, type)

    '''###################
    	measure freq		
    ###################'''
    print "[%s:%d] ===== sine ===============" % (thisfile(), linenum())

    result_sines = wl.measure_Frequency_3(wf_sines)
#     result = wl.measure_Frequency(wf_sines)
    
    print "[%s:%d] freq of sines => %d" % (thisfile(), linenum(), result_sines)

    print "[%s:%d] ===== cosine ===============" % (thisfile(), linenum())

    result_cosines = wl.measure_Frequency_3(wf_cosines)
#     result = wl.measure_Frequency(wf_sines)
    
    print "[%s:%d] freq of cosines => %d" % (thisfile(), linenum(), result_cosines)
    
    
    '''###################
    	ending		
    ###################'''
    print "[%s:%d] exec_2__Measure_Frequency ==> done" % (thisfile(), linenum())
    		
    
    '''###################
    	return		
    ###################'''
    return

def exec_3__Measure_Frequency_SinePlusCosine():
    
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
    	prep : wf : sine
    ###################'''
    A = 1.0; fs = 8000.0; length = 1.0; phase = 1.0; type = "sine"
    
    f0_val = [x[1] for x in options if x[0] == '-f'][0]
    
    f0 = int(f0_val);
#     f0 = 262 * wl.EQUAL_TEMPERAMENTS[6];
#     f0 = 262 * wl.EQUAL_TEMPERAMENTS[3];
#     f0 = 262;
    
    timelabel = get_TimeLabel_Now()
    
    fname_sines = "test_1.sines.%s.f0=%d_phase-%1.2f.wav" % (timelabel, f0, phase)
    
    wf_sines = wl.get_WaveFile__Sines (fname_sines, A, f0, fs, length, phase, type)

    '''###################
    	prep : wf : cosine
    ###################'''
    A = 1.0; fs = 8000.0; length = 1.0; phase = 1.0; type = "cosine"
    
    f0_val = [x[1] for x in options if x[0] == '-f'][0]
    
    f0 = int(f0_val);
#     f0 = 262 * wl.EQUAL_TEMPERAMENTS[6];
#     f0 = 262 * wl.EQUAL_TEMPERAMENTS[3];
#     f0 = 262;
    
    timelabel = get_TimeLabel_Now()
    
    fname_cosines = "test_1.cosines.%s.f0=%d_phase-%1.2f.wav" % (timelabel, f0, phase)
    
    wf_cosines = wl.get_WaveFile__Sines (fname_cosines, A, f0, fs, length, phase, type)

    '''###################
    	prep : wf : sine + cosine
    ###################'''
    fname_SinesCosines = "test_1.sines+cosines.%s.f0=%d_phase-%1.2f.wav" \
    						% (timelabel, f0, phase)
    						
    wf_SinesCosines = wl.copy_WaveFile(wf_sines, fname_new=fname_SinesCosines)
    
    ### add analog data
    pairsOf_analogdata = zip(wf_sines.analogdata, wf_cosines.analogdata)
    
    analogdata_Stardardized = [1/sqrt(2) * (x + y) for x, y in pairsOf_analogdata]
    
    wf_SinesCosines.analogdata = analogdata_Stardardized
#     wf_SinesCosines.data = analogdata_Stardardized

    '''###################
    	measure freq		
    ###################'''
    print "[%s:%d] ===== sine ===============" % (thisfile(), linenum())

    result_sines = wl.measure_Frequency_3(wf_sines)
#     result = wl.measure_Frequency(wf_sines)
    
    print "[%s:%d] freq of sines => %d" % (thisfile(), linenum(), result_sines)

    print "[%s:%d] ===== cosine ===============" % (thisfile(), linenum())

    result_cosines = wl.measure_Frequency_3(wf_cosines)
#     result = wl.measure_Frequency(wf_sines)
    
    print "[%s:%d] freq of cosines => %d" % (thisfile(), linenum(), result_cosines)
    
    print "[%s:%d] ===== sine + cosine ===============" % (thisfile(), linenum())

    result_SinesCosines = wl.measure_Frequency_3(wf_SinesCosines)
    
    print "[%s:%d] freq of SinesCosines => %d" \
        % (thisfile(), linenum(), result_SinesCosines)
    
    
    print "[%s:%d] ===== sine ^ 2 ===============" % (thisfile(), linenum())
 
    fname_SinesSquared = "test_1.sines+cosines.%s.f0=%d_phase-%1.2f.wav" \
    						% (timelabel, f0, phase)
     						
    wf_SinesSquared = wl.copy_WaveFile(wf_sines, fname_new=fname_SinesSquared)
     
    ### add analog data
# 	pairsOf_analogdata = zip(wf_sines.analogdata, wf_cosines.analogdata)
     
    analogdata_Squared = [pow(x, 2) for x in wf_sines.analogdata]
#     analogdata_Squared = [x^2 for x in wf_sines.analogdata]
     
    wf_SinesSquared.analogdata = analogdata_Squared
 
    result_SinesSquared = wl.measure_Frequency_3(wf_SinesSquared)
     
    print "[%s:%d] freq of SinesSquared => %d" \
    			% (thisfile(), linenum(), result_SinesSquared)
     
    print "[%s:%d] ===== sine(x) + sine(x + %%pi/2) ===============" \
    			% (thisfile(), linenum())
 
    fname_SinesPlusSinesPIover2 = "test_1.sine(x)+sine(x+PIover2).%s.f0=%d_phase-%1.2f.wav" \
    						% (timelabel, f0, phase)
     						
    wf_SinesPlusSinesPIover2 = wl.copy_WaveFile(wf_sines, fname_new=fname_SinesPlusSinesPIover2)
     
    ### add analog data
    nomi = 30
    n = 5
#     n = 20		#=> [test_1.py:327] freq of SinesPlusSinesPIover2 => 20
	   			# [test_1.py:328] (nomi = 30 / n = 20)
#     n = 10	#=> [test_1.py:325] freq of SinesPlusSinesPIover2 => 20
    
    analogdata_Squared = [x + np.pi / nomi * n for x in wf_sines.analogdata]
#     analogdata_Squared = [x + np.pi / 2 for x in wf_sines.analogdata]
     
    wf_SinesPlusSinesPIover2.analogdata = analogdata_Squared
 
    result_SinesPlusSinesPIover2 = wl.measure_Frequency_3(wf_SinesPlusSinesPIover2)
     
    print "[%s:%d] freq of SinesPlusSinesPIover2 => %d" \
    			% (thisfile(), linenum(), result_SinesPlusSinesPIover2)
    print "[%s:%d] (nomi = %d / n = %d)" % (thisfile(), linenum(), nomi, n)
    
     
    
    print "[%s:%d] ===== sine(x + A) + sine(x + B) ===============" \
    			% (thisfile(), linenum())
 
    fname_SinesAPlusSinesB = "test_1.sine(x+A)+sine(x+B).%s.f0=%d_phase-%1.2f.wav" \
    						% (timelabel, f0, phase)
     						
    wf_SinesAPlusSinesB = wl.copy_WaveFile(wf_sines, fname_new=fname_SinesAPlusSinesB)
     
    ### add analog data
    nomi = 30
    n_1 = 5
    n_2 = 10
#     n = 20		#=> [test_1.py:327] freq of SinesPlusSinesPIover2 => 20
	   			# [test_1.py:328] (nomi = 30 / n = 20)
#     n = 10	#=> [test_1.py:325] freq of SinesPlusSinesPIover2 => 20
    
    analogdata_Squared = [\
				(x + np.pi / nomi * n_1) + (x + np.pi / nomi * n_2) \
				for x in wf_sines.analogdata]
#     analogdata_Squared = [x + np.pi / nomi * n for x in wf_sines.analogdata]
#     analogdata_Squared = [x + np.pi / 2 for x in wf_sines.analogdata]
     
    wf_SinesAPlusSinesB.analogdata = analogdata_Squared
 
    result_SinesAPlusSinesB = wl.measure_Frequency_3(wf_SinesAPlusSinesB)
     
    print "[%s:%d] freq of SinesAPlusSinesB => %d" \
    			% (thisfile(), linenum(), result_SinesAPlusSinesB)
    print "[%s:%d] (nomi = %d / n = %d)" % (thisfile(), linenum(), nomi, n)
    
     
    
    '''###################
    	ending		
    ###################'''
    print "[%s:%d] exec_2__Measure_Frequency ==> done" % (thisfile(), linenum())
    		
    
    '''###################
    	return		
    ###################'''
    return
#]]exec_3__Measure_Frequency_SinePlusCosine
    
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
    exec_3__Measure_Frequency_SinePlusCosine()
#     exec_2__Measure_Frequency_Others()
#     exec_1__Measure_Frequency()
    
    print
    print "[%s:%d] done" % (thisfile(), linenum())
