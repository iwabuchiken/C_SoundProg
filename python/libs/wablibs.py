###############################################
import sys
sys.path.append('.')
from libs import *
# from libs.libs import *

import getopt
import os
import inspect
###############################################


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
    
#     def __init__(self, fname = '', bindata = None, nchannels = 1) :    #=> works
    def __init__(self, fname = '', bindata = None, nchannels=1,\
                 samplewidth=8000, framerate=None, nframes=None,\
                 comptype=None, compname=None, analogdata = None) :
        
        self.fname = fname
        
        self.bindata = bindata
        self.nchannels  = nchannels
        self.samplewidth    = samplewidth
        self.framerate=framerate
        self.nframes=nframes
        self.comptype   = comptype
        self.compname   = compname
        self.analogdata   = analogdata
        

def copy_WaveFile(wavefile_src, fname_new=''):
    
    wf = WaveFile()
    
    if fname_new == '' :
        
        fname_trunk, fname_ext = os.path.splitext(wavefile_src.fname)
        
        wf.fname = "%s.%s.%s" % (fname_trunk, "copy", fname_ext)
    
    else :
        
        wf.fname = fname_new
        
#     wf.fname = wavefile_src.fname
        
    wf.bindata = wavefile_src.bindata
    wf.nchannels  = wavefile_src.nchannels
    wf.samplewidth    = wavefile_src.samplewidth
    wf.framerate= wavefile_src.framerate
    wf.nframes= wavefile_src.nframes
    wf.comptype   = wavefile_src.comptype
    wf.compname   = wavefile_src.compname
    wf.analogdata   = wavefile_src.analogdata

    return wf