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

def createSineWave (A, f0, fs, length):
	"""振幅A、基本周波数f0、サンプリング周波数 fs、
	長さlength秒の正弦波を作成して返す"""
	data = []
	# [-1.0, 1.0]の小数値が入った波を作成
	for n in arange(length * fs):  # nはサンプルインデックス
		s = A * np.sin(2 * np.pi * f0 * n / fs)
		# 振幅が大きい時はクリッピング
		if s > 1.0:  s = 1.0
		if s < -1.0: s = -1.0
		data.append(s)
	# [-32768, 32767]の整数値に変換
	data = [int(x * 32767.0) for x in data]
#	plot(data[0:100]); show()
	# バイナリに変換
	data = struct.pack("h" * len(data), *data)  # listに*をつけると引数展開される
	return data

def createSineWave_2 (A, f0, fs, length):
	"""振幅A、基本周波数f0、サンプリング周波数 fs、
	長さlength秒の正弦波を作成して返す"""
	data = []
	# [-1.0, 1.0]の小数値が入った波を作成
	for n in arange(length * fs):  # nはサンプルインデックス
		s = A * np.sin(2 * np.pi * f0 * n / fs)
		# 振幅が大きい時はクリッピング
		if s > 1.0:  s = 1.0
		if s < -1.0: s = -1.0
		data.append(s)
		
	# [-32768, 32767]の整数値に変換
	bindata = [int(x * 32767.0) for x in data]
#	plot(data[0:100]); show()
	# バイナリに変換
	bindata = struct.pack("h" * len(bindata), *bindata)  # listに*をつけると引数展開される
	
	return (data, bindata)
# 	return data

def play (data, fs, bit):
	import pyaudio
	# ストリームを開く
	p = pyaudio.PyAudio()
	stream = p.open(format=pyaudio.paInt16,
					channels=1,
					rate=int(fs),
					output= True)
	# チャンク単位でストリームに出力し音声を再生
	chunk = 1024
	sp = 0  # 再生位置ポインタ
	buffer = data[sp:sp+chunk]
	while buffer != '':
		stream.write(buffer)
		sp = sp + chunk
		buffer = data[sp:sp+chunk]
	stream.close()
	p.terminate()
	
def data_Absolutize(wavefile, generate_new = False, fname = '') :
# def data_Absolutize(wavefile, generate_new = True, fname = '') :
	
	###################
	#	init : wf		
	#####################
	wf = None
	
	if generate_new == True : wf = wl.WaveFile()
	else : wf = wavefile

	###################
	#	absolutize : analog	
	#####################
	print "[%s:%d] len(wf.analogdata) => %d" % (thisfile(), linenum(), len(wf.analogdata))
						
	length = len(wf.analogdata)
						
	wf.analogdata = [math.fabs(wf.analogdata[i]) for i in range(len(wf.analogdata))]
# 	wf.analogdata = [math.fabs(wf.analogdata[i]) for i in wf.analogdata]
						
# 	for i in range(length) :
# 		
# 		wf.analogdata[i] = math.fabs(wf.analogdata[i])
		
	###################
	#	absolutize : binary	
	#####################
	wf.bindata = [int(x * 32767.0) for x in wf.analogdata]
	
	wf.bindata = struct.pack("h" * len(wf.bindata), *wf.bindata)
		
	'''###################
		return		
	###################'''
	return wf
	
def amplitude_Down(wavefile, val) :
	
	baseval = 1000
	
	wavefile.analogdata = [ wavefile.analogdata[i] * \
							val / 1000.0 for i in range(len(wavefile.analogdata))]
	
	wavefile.bindata = [int(x * 32767.0) for x in wavefile.analogdata]
	
	wavefile.bindata = struct.pack("h" * len(wavefile.bindata), *wavefile.bindata)

	return wavefile
	
def exec_1():
	
	'''###################
		Build wavefile : source
	   #####################'''
	freqList = [262, 294, 330, 349, 392, 440, 494, 523]  # ドレミファソラシド
	
	timelabel = get_TimeLabel_Now()

	"""振幅A、基本周波数f0、サンプリング周波数 fs、
	長さlength秒の正弦波を作成して返す"""
	#createSineWave (A, f0, fs, length)
	A = 1.0
	f0 = freqList[0]
	fs = 16000.0
# 	fs = 44100.0
# 	fs = 8000.0
	length = 2.0
# 	length = 1.0
	
	(analogdata, bindata) = createSineWave_2(A, f0, fs, length)
# 	(analogdata, bindata) = createSineWave_2(1.0, f[0], 8000.0, 1.0)
	
	dpath = "audio"
	
	fname = "test_1.sine-%d.%s.wav" % (f0, timelabel)
	
	fpath = "%s/%s" % (dpath, fname)
	
	wf = wl.WaveFile(fname)
		
	wf.nchannels  = 1
	wf.samplewidth	= fs
# 	wf.framerate=framerate
# 	wf.nframes=nframes
# 	wf.comptype   = wavefile_src.comptype
# 	wf.compname   = wavefile_src.compname
	wf.analogdata   = analogdata
	wf.bindata = bindata

	print "[%s:%d] wf =>" % (thisfile(), linenum())
	
	for i in range(100, 110) :
# 	for i in range(0, 10) :
		
		print "wf.analogdata[%d] = %f" % (i, wf.analogdata[i])
# 		print "analogdata[%d] = %f" % (i, analogdata[i])
	
	'''###################
		save file : wf		
	#####################'''
	dpath_dst = "audio"
	
	wl.save_WaveFile__Class(wf, dpath_dst=dpath_dst)

	
	'''###################
		abosolutize		
	###################'''
	data_Absolutize(wf)
	
	print "[%s:%d] absolutize => processed" % (thisfile(), linenum())
	
	for i in range(100, 110) :
# 	for i in range(0, 10) :
	
		print "wf.analogdata[%d] = %f" % (i, wf.analogdata[i])
# 		print "analogdata[%d] = %f" % (i, analogdata[i])

	'''###################
		save file : wf		
	#####################'''
	dpath_dst = "audio"
	
	fname_trunk, fname_ext = os.path.splitext(wf.fname)
	
	wf.fname = "%s_Absolute%s" % (fname_trunk, fname_ext)
	
	wl.save_WaveFile__Class(wf, dpath_dst=dpath_dst)

	print "[%s:%d] file saved => '%s'" % (thisfile(), linenum(), wf.fname)
	

#]]def exec_4()

def exec_2(options):
	
	'''###################
		Build wavefile : source
	   #####################'''
	freqList = [262, 294, 330, 349, 392, 440, 494, 523]  # ドレミファソラシド
	
	timelabel = get_TimeLabel_Now()

	"""振幅A、基本周波数f0、サンプリング周波数 fs、
	長さlength秒の正弦波を作成して返す"""
	#createSineWave (A, f0, fs, length)
	A = 1.0
	f0 = freqList[0]
# 	fs = 16000.0
# 	fs = 44100.0
	fs = 8000.0
	length = 2.0
# 	length = 1.0
	
	(analogdata, bindata, radians) = wl.createSineWave(A, f0, fs, length)
# 	(analogdata, bindata) = createSineWave_2(A, f0, fs, length)
# 	(analogdata, bindata) = createSineWave_2(1.0, f[0], 8000.0, 1.0)
	
	dpath = "audio"
	
	fname = "test_1.sine-%d.%s.wav" % (f0, timelabel)
	
	fpath = "%s/%s" % (dpath, fname)
	
	wf = wl.WaveFile(fname)
		
	wf.nchannels  = 1
	wf.samplewidth	= fs
# 	wf.framerate=framerate
# 	wf.nframes=nframes
# 	wf.comptype   = wavefile_src.comptype
# 	wf.compname   = wavefile_src.compname
	wf.analogdata   = analogdata
	wf.bindata = bindata
	wf.radians = radians

	print "[%s:%d] wf =>" % (thisfile(), linenum())
	
	for i in range(100, 110) :
# 	for i in range(0, 10) :
		
		print "wf.analogdata[%d] = %f (radian = %f)" % (i, wf.analogdata[i], wf.radians[i])
# 		print "wf.analogdata[%d] = %f" % (i, wf.analogdata[i])
# 		print "analogdata[%d] = %f" % (i, analogdata[i])
	
	'''###################
		save file : wf		
	#####################'''
	dpath_dst = "audio"
	
	wl.save_WaveFile__Class(wf, dpath_dst=dpath_dst)

	
	'''###################
		Amplitude down	
	###################'''
	### set value
	val = None
	
# 	print "[%s:%d] len(result) => %d" % (thisfile(), linenum(), len(result))

# 	print "[%s:%d] options =>" % (thisfile(), linenum())

# 	print options
	
	for pair in options :
# 	for pair in result :
		if pair[0] == '-v' :
			val = int(pair[1])
	
	if val == None : val = 200	# default value
	
# 	val = 200	# 600/1000
# 	val = 600	# 600/1000

	amplitude_Down(wf, val)
	
	print "[%s:%d] absolutize => processed" % (thisfile(), linenum())
	
# 	for i in range(100, 110) :
# # 	for i in range(0, 10) :
# 	
# 		print "wf.analogdata[%d] = %f" % (i, wf.analogdata[i])
# # 		print "analogdata[%d] = %f" % (i, analogdata[i])

	'''###################
		save file : wf		
	#####################'''
	dpath_dst = "audio"
	
	fname_trunk, fname_ext = os.path.splitext(wf.fname)
	
	description = "Amplitude-down"
	
	wf.fname = "%s_%s_val-%d%s" % (fname_trunk, description, val, fname_ext)
	
	wl.save_WaveFile__Class(wf, dpath_dst=dpath_dst)

	print "[%s:%d] file saved => '%s'" % (thisfile(), linenum(), wf.fname)
	

#]]def exec_4()
#]]def exec_2()

def test_1_GetOpt():

	keychars = "v"
	
	print "[%s:%d] sys.argv =>" % (thisfile(), linenum())

	print sys.argv
	
	result = get_opt_2(sys.argv, keychars)
	
	print result

def test_2_Get_SineWF(options):
	
# 	print options
	freqList = [262, 294, 330, 349, 392, 440, 494, 523]  # ドレミファソラシド
	
	timelabel = get_TimeLabel_Now()

	"""振幅A、基本周波数f0、サンプリング周波数 fs、
	長さlength秒の正弦波を作成して返す"""
	#createSineWave (A, f0, fs, length)
	### param : A
	A = 1.0
	
	### param : f0
	f0 = None
	
	#ref x in a : https://stackoverflow.com/questions/7571635/fastest-way-to-check-if-a-value-exist-in-a-list "answered Sep 27 '11 at 15:25"
	aryOf_f0 = [x for x in options if x[0] == '-f']
	lenOf_f0 = len(aryOf_f0)
	
	if lenOf_f0 > 0 : f0 = int(aryOf_f0[0][1])
# 	if lenOf_f0 > 0 : f0 = aryOf_f0[0][1]
	else : f0 = freqList[0]		# default
	
	### param : phase
	phase = None
	
	aryOf_phase = [x for x in options if x[0] == '-p']
	lenOf_phase = len(aryOf_phase)
	
	if lenOf_phase > 0 : phase = float(aryOf_phase[0][1])
# 	if lenOf_f0 > 0 : f0 = aryOf_f0[0][1]
	else : phase = 1.0		# default
	
# 	if "-v" in [x[0] for x in options] : f0 = 
	
# 	f0 = freqList[0]
	
	### param : fs
# 	fs = 16000.0
# 	fs = 44100.0
	fs = 8000.0
	
	### param : length
	length = 2.0
# 	length = 1.0
	
	### param : data
	(analogdata, bindata, radians) = wl.createSineWave(A, f0, fs, length)
# 	(analogdata, bindata) = createSineWave_2(A, f0, fs, length)
# 	(analogdata, bindata) = createSineWave_2(1.0, f[0], 8000.0, 1.0)
	
	### param : file name, file path
	dpath = "audio"
	
	fname = "test_1.sine-%d.%s.wav" % (f0, timelabel)
	
	fpath = "%s/%s" % (dpath, fname)

	'''###################
			build : wavefile		
		###################'''
	wf = wl.get_WaveFile__Sines(fname, A, f0, fs, length, phase = 1.0)
	
	dpath_dst = "audio"
	
	wl.save_WaveFile__Class(wf, dpath_dst=dpath_dst)

	print "[%s:%d] file saved => '%s'" % (thisfile(), linenum(), fname)
	
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
	
# 	print sys.argv
	
	result = get_opt_2(sys.argv, keychars)

# 	result = test_1_GetOpt()
	
	'''###################
		evecute		
	###################'''

	test_2_Get_SineWF(result)
# 	exec_2(result)
# 	exec_1()

	print
	print "[%s:%d] done" % (thisfile(), linenum())
							
