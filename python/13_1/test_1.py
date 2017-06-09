# -*- coding: utf-8 -*-
'''
pushd C:\WORKS_2\WS\Eclipse_Luna\C_SoundProg\python\13_1
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

def exec_1_Equal_Temperament():
		
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
	
	### test
	wl.get_SineWF(1.0, 262, fs = 8000.0, phase=1.0, length=1.0, dpath = "audio", fname='')

	'''
		Gen sounds
	'''
	A = 1.0; fs = 8000.0; phase = 1.0; length = 2.0; dpath = 'audio'
	
	timelabel = get_TimeLabel_Now()
	
	base_tone = 262		# 'A' pitch
	
	for val in values :
		
		fname = "test_1.EqualTempera.val-%.6f_tone-%.3f_A-%.3f_phase-%.3f_len-%.3f.%s.wav" \
				% (val, (base_tone * val), A, phase, length, timelabel)
		
		wf = wl.get_SineWF(A, base_tone * val, fs, phase, length, dpath, fname)
		
		dpath_dst = "audio"
	
		print "[%s:%d] wf.fname => '%s'" % (thisfile(), linenum(), wf.fname)
	
		wl.save_WaveFile__Class(wf, dpath_dst=dpath_dst)

	
		
	return
				
def exec_2_Random_Pitches():

	'''
		Gen sounds
	'''
	A = 1.0; fs = 8000.0; phase = 1.0; length = 1.0; dpath = 'audio'
# 	A = 1.0; fs = 8000.0; phase = 1.0; length = 2.0; dpath = 'audio'
	
	timelabel = get_TimeLabel_Now()
	
	base_tone = 262		# 'A' pitch

	#ref seed https://docs.python.jp/3/library/random.html
	rnd.seed()
	#ref https://stackoverflow.com/questions/4172131/create-random-list-of-integers-in-python 'answered Nov 13 '10 at 11:14'
	#ref http://www.python-izm.com/contents/application/random.shtml
	indexes = [rnd.randint(0, len(values) - 1) for i in range(0, 8)]
# 	indexes = [rnd.randint(0, len(values)) for i in range(0, 8)]
	
	count = 1
	
	for num in indexes :
# 	for val in values :
		
		base_tone = 262
# 		base_tone = values[num]

		current_tone = base_tone * values[num]
		
		#ref multiple string https://stackoverflow.com/questions/10660435/pythonic-way-to-create-a-long-multi-line-string 'answered May 18 '12 at 22:22'
		fname = "test_1.EqualTempera.%s.(%d).base-%d_val-%.6f"\
			"_tone-%.3f_A-%.3f_phase-%.3f_len-%.3f.wav" \
				% (timelabel, count, base_tone, values[num], \
				(base_tone * values[num]), A, phase, length)
# 		fname = "test_1.EqualTempera.val-%.6f_tone-%.3f_A-%.3f_phase-%.3f_len-%.3f.%s.wav" \
# 				% (val, (base_tone * val), A, phase, length, timelabel)
		
		wf = wl.get_SineWF(A, current_tone, fs, phase, length, dpath, fname)
# 		wf = wl.get_SineWF(A, base_tone * val, fs, phase, length, dpath, fname)
		
		dpath_dst = "audio"
	
		print "[%s:%d] wf.fname => '%s'" % (thisfile(), linenum(), wf.fname)
	
		wl.save_WaveFile__Class(wf, dpath_dst=dpath_dst)
		
		# increment count
		count += 1
	
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
	exec_2_Random_Pitches()
# 	exec_1_Equal_Temperament()
 	
 	
	print
	print "[%s:%d] done" % (thisfile(), linenum())
