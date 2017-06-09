# -*- coding: utf-8 -*-
'''
pushd C:\WORKS_2\WS\Eclipse_Luna\C_SoundProg\python\12_1
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

def show_Message() :
				
	msg = '''
	<Options>
	-v	Volume down the amplitude --> 1.0 * v / 1000
	-f	Base frequency ---> e.g. 262 for the A tone
	-p	Phase of the sine curves ---> sin(2 * np.pi * f0 * n * phase / fs)'''
	
	print msg
	
				
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

	print
	print "[%s:%d] done" % (thisfile(), linenum())
							
