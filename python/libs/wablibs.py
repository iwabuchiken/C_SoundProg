import wave
import struct
import numpy as np
from time import sleep

'''
    @param
    binwave    => binwave = struct.pack("h" * len(swav), *swav) : C:\WORKS_2\WS\Eclipse_Luna\C_SoundProg\python\test.py
'''
def save_WaveFile(fname, binwave, comptype='NONE', compname='not compressed'):
    
	w = wave.Wave_write(fname)
# 	w = wave.Wave_write("output.wav")
    
	p = (1, 2, 8000, len(binwave), comptype, compname)
# 	p = (1, 2, 8000, len(binwave), 'NONE', 'not compressed')
    
    
	w.setparams(p)
    
	w.writeframes(binwave)
    
	w.close()

# def copy_WaveFile(binwave):
    
#ref https://en.wikibooks.org/wiki/A_Beginner%27s_Python_Tutorial/Classes
class WaveFile :
    
#     def __init__(self, fname = '', binwave = None, nchannels = 1) :    #=> works
    def __init__(self, fname = '', binwave = None, nchannels=1,\
                 samplewidth=8000, framerate=None, nframes=None,\
                 comptype=None, compname=None, analogwave = None) :
        
        self.fname = fname
        
        self.binwave = binwave
        self.nchannels  = nchannels
        self.samplewidth    = samplewidth
        self.framerate=framerate
        self.nframes=nframes
        self.comptype   = comptype
        self.compname   = compname
        self.analogwave   = analogwave
        
    
	#ref https://docs.python.jp/3/library/wave.html
	#(nchannels, sampwidth, framerate, nframes, comptype, compname)
	#ref C:\WORKS_2\WS\Eclipse_Luna\C_SoundProg\python\test.py
	#(1, 2, 8000, len(binwave), 'NONE', 'not compressed') 
# 	def __init__(self, fname = '', binwave=None, nchannels=1, samplewidth=8000, \
# 	def __init__(self, fname = '', binwave=None, nchannels=1, samplewidth=8000, \
# 				 framerate=None, nframes=None,\
# 				 comptype=None, compname=None):
# 		self.fname    = fname
# 		self.binwave  = binwave
# #         self.nchannels  = nchannels
#         self.samplewidth    = samplewidth
#         self.framerate  = framerate 
#         self.nframes    = nframes
#         self.comptype   = comptype 
#         self.compname   = compname



