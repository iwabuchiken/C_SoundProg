# -*- coding: utf-8 -*-
'''
pushd C:\WORKS_2\WS\Eclipse_Luna\C_SoundProg\python\14_1
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

values = [1.000000,
			1.059463,
			1.122462,
			1.189207,
			1.259921,
			1.334840,
			1.414214,
			1.498307,
			1.587401,
			1.681793,
			1.781797,
			1.887749,
			2.000000]

def show_Message() :
				
	msg = '''
	<Options>
	-v	Volume down the amplitude --> 1.0 * v / 1000
	-f	Base frequency ---> e.g. 262 for the A tone
	-p	Phase of the sine curves ---> sin(2 * np.pi * f0 * n * phase / fs)'''
	
	print msg

def exec_1__SinePlusCosine():
	
	'''###################
		prep : wfs		
	###################'''
	A = 1.0; f0 = 262; fs = 8000.0; length = 1.0; phase = 1.0; type = "sine"
	
	timelabel = get_TimeLabel_Now()
	
	fname_sines = "test_1.sines.%s.f0=%d_phase-%1.2f.wav" % (timelabel, f0, phase)
	
	wf_sines = wl.get_WaveFile__Sines (fname_sines, A, f0, fs, length, phase, type)
	
	fname_cosines = "test_1.cosines.%s.f0=%d_phase-%1.2f.wav" % (timelabel, f0, phase)
	
	wf_cosines = wl.get_WaveFile__Sines (fname_cosines, A, f0, fs, length, phase, "cosine")
	
	'''###################
		save : wav fles		
	###################'''
	dpath_dst = "audio"
	
	wl.save_WaveFile__Class(wf_sines, dpath_dst=dpath_dst)
 	
	wl.save_WaveFile__Class(wf_cosines, dpath_dst=dpath_dst)

	'''###################
		addition : sines + cosines		
	###################'''
	pairsOf_analogdata = zip(wf_sines.analogdata, wf_cosines.analogdata)
	
	analogdata_Stardardized = [1/sqrt(2) * (x + y) for x, y in pairsOf_analogdata]

	fname_addition = "test_1.addition.%s.wav" % (timelabel)

	wf_addition = wl.get_WaveFile__AnalogData(\
				fname_addition, analogdata_Stardardized, A, \
				length, nchannels = 1, \
				radians = wf_sines.radians, \
				f0 = wf_sines.basefreq)

	wl.save_WaveFile__Class(wf_addition, dpath_dst=dpath_dst)
	
	
	'''###################
		ending		
	###################'''
	print "[%s:%d] exec_1__SinePlusCosine ==> done" % (thisfile(), linenum())
			
	
	return

def exec_1_1__SinePlusCosine_Clipping():
	
	'''###################
		prep : wfs		
	###################'''
	A = 1.0; f0 = 262; fs = 8000.0; length = 1.0; phase = 1.0; type = "sine"
	
	timelabel = get_TimeLabel_Now()
	
	fname_sines = "test_1.sines.%s.f0=%d_phase-%1.2f.wav" % (timelabel, f0, phase)
	
	wf_sines = wl.get_WaveFile__Sines (fname_sines, A, f0, fs, length, phase, type)
	
	fname_cosines = "test_1.cosines.%s.f0=%d_phase-%1.2f.wav" % (timelabel, f0, phase)
	
	wf_cosines = wl.get_WaveFile__Sines (fname_cosines, A, f0, fs, length, phase, "cosine")
	
	'''###################
		save : wav fles		
	###################'''
	dpath_dst = "audio"
	
	wl.save_WaveFile__Class(wf_sines, dpath_dst=dpath_dst)
 	
	wl.save_WaveFile__Class(wf_cosines, dpath_dst=dpath_dst)

	'''###################
		addition : sines + cosines		
	###################'''
	pairsOf_analogdata = zip(wf_sines.analogdata, wf_cosines.analogdata)
	
# 	analogdata_Stardardized = [1/sqrt(2) * (x + y) for x, y in pairsOf_analogdata]
	analogdata_Stardardized = []
	
	for pair in pairsOf_analogdata :
		
		sum = pair[0] + pair[1]
		
		if sum > 1.0 : sum = 1.0
		if sum < -1.0 : sum = -1.0
		
		analogdata_Stardardized.append(sum)

	fname_addition = "test_1.addition-clipped.%s.wav" % (timelabel)

	wf_addition = wl.get_WaveFile__AnalogData(\
				fname_addition, analogdata_Stardardized, A, \
				length, nchannels = 1, \
				radians = wf_sines.radians, \
				f0 = wf_sines.basefreq)

	wl.save_WaveFile__Class(wf_addition, dpath_dst=dpath_dst)
	
	
	'''###################
		ending		
	###################'''
	print "[%s:%d] exec_1__SinePlusCosine ==> done" % (thisfile(), linenum())
			
	
	return
#]]exec_1_1__SinePlusCosine_Clipping()

	
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
 	exec_1_1__SinePlusCosine_Clipping()
#  	exec_1__SinePlusCosine()
 	
	print
	print "[%s:%d] done" % (thisfile(), linenum())
