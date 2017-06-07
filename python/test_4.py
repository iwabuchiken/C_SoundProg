# -*- coding: utf-8 -*-
'''
pushd C:\WORKS_2\WS\Eclipse_Luna\C_SoundProg\python
test2.py

ref : http://aidiary.hatenablog.com/entry/20110607/1307449007

'''
###############################################
import sys
sys.path.append('.')
from libs.libs import *
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

def exec_1():

	freqList = [262, 294, 330, 349, 392, 440, 494, 523]  # ドレミファソラシド

	wflist = []
	
	timelabel = get_TimeLabel_Now()
	
	for f in freqList:

		"""
		振幅A、基本周波数f0、サンプリング周波数 fs、
		長さlength秒の正弦波を作成して返す
		createSineWave (A, f0, fs, length)
		"""
		(analogdata, bindata) = createSineWave_2(1.0, f, 8000.0, 1.0)
# 		data = createSineWave(1.0, f, 8000.0, 1.0)
		
		fname = "test_2.sinewave-%d.%s.wav" % (f, timelabel)
#		 fname = "test_2.sinewave-%d.%s.wav" % (f, get_TimeLabel_Now())
		
		wf = wl.WaveFile(fname)
		
		wf.samplewidth = 8000
		
		wf.binwave = bindata
		wf.analogdata = analogdata
		
		wflist.append(wf)
		
	for wf in wflist :
		
 		print "[%s:%d] fname => '%s' (nchannels = %d / samplewidth = %f)" \
			% (thisfile(), linenum(), wf.fname,\
			wf.nchannels, wf.samplewidth)
		
		print "[%s:%d] data => " % (thisfile(), linenum())
		print wf.binwave[0:10]
		print wf.analogdata[0:10]
#]]def exec_1()
	
def exec_2():
	
	freqList = [262, 294, 330, 349, 392, 440, 494, 523]  # ドレミファソラシド
	
	timelabel = get_TimeLabel_Now()

	"""振幅A、基本周波数f0、サンプリング周波数 fs、
	長さlength秒の正弦波を作成して返す"""
	#createSineWave (A, f0, fs, length)
	A = 1.0
	f0 = freqList[0]
	fs = 8000.0
	length = 1.0
	
	(analogdata, bindata) = createSineWave_2(A, f0, fs, length)
# 	(analogdata, bindata) = createSineWave_2(1.0, f[0], 8000.0, 1.0)
	
	dpath = "audio"
	
	fname = "test_2.sinewave-%d.%s.wav" % (f0, timelabel)
	
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


	for i in range(0, 10) :
		
		print "analogdata[%d] = %f" % (i, analogdata[i])
#[[def exec_2()

def exec_3():
	
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
	fs = 8000.0
	length = 1.0
	
	(analogdata, bindata) = createSineWave_2(A, f0, fs, length)
# 	(analogdata, bindata) = createSineWave_2(1.0, f[0], 8000.0, 1.0)
	
	dpath = "audio"
	
	fname = "test_2.sinewave-%d.%s.wav" % (f0, timelabel)
	
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
	
	for i in range(0, 10) :
		
		print "analogdata[%d] = %f" % (i, analogdata[i])

	'''###################
		copy
	   #####################'''
	wf_2 = wl.copy_WaveFile(wf)
# 	wf_2 = wablibs.copy_WaveFile(wf)

	### report
	for i in range(0, 10) :
		
		print "wf_2.analogdata[%d] = %f" % (i, wf_2.analogdata[i])
	
def exec_4():
	
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
	fs = 8000.0
	length = 1.0
	
	(analogdata, bindata) = createSineWave_2(A, f0, fs, length)
# 	(analogdata, bindata) = createSineWave_2(1.0, f[0], 8000.0, 1.0)
	
	dpath = "audio"
	
	fname = "test_2.sinewave-%d.%s.wav" % (f0, timelabel)
	
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
	
	for i in range(0, 10) :
		
		print "analogdata[%d] = %f" % (i, analogdata[i])

	'''###################
		save file : wf		
	#####################'''
	dpath_dst = "audio"
	
	wl.save_WaveFile__Class(wf, dpath_dst=dpath_dst)
# 	wl.save_WaveFile__Class(wf, dpath_dst)
# 	wl.save_WaveFile__Class(wf)

	'''###################
		copy
	   #####################'''
	wf_2 = wl.copy_WaveFile(wf)
# 	wf_2 = wablibs.copy_WaveFile(wf)

	### report
	for i in range(0, 10) :
		
		print "wf_2.analogdata[%d] = %f" % (i, wf_2.analogdata[i])

	print "[%s:%d] wf_2.fname => '%s'" % (thisfile(), linenum(), wf_2.fname)
	

	'''###################
		save file		
	#####################'''
	wl.save_WaveFile__Class(wf_2, dpath_dst=dpath_dst)
# 	wl.save_WaveFile__Class(wf_2, dpath_dst)
# 	wl.save_WaveFile__Class(wf_2)

#]]def exec_4()



if __name__ == "__main__" :

	exec_4()
# 	exec_3()
# 	exec_2()
# 	exec_1()

print "yes"
