import numpy as np
import matplotlib.pyplot as plt

class Analyse:

    def __init__(self, sample_rate=0, size=0.0):
        self.arr = []
        self.fft_arr = []
        self.ifft_arr = []
        self.positive = False
        self.sample_rate = sample_rate
        self.size = size

    def update(self, arr=[], ts = [], sample_rate=0, size=0):
        self.__init__(sample_rate, size)
        self.arr = arr
        self.ts = ts

    def draw(self, arr=None, base=None, xlim=None, ylim=None, color=None, title=None):
        if arr is None:
            arr = self.arr[: size]
            base = self.ts
        if base is None:
            plt.plot(arr, color=color)
        else:
            plt.plot(base, arr, color=color)
        if xlim is not None:
            (up, down) = xlim
            plt.xlim(up, down)
        if ylim is not None:
            (up, down) = ylim
            plt.ylim(up, down)
        if title is not None:
            plt.title(title)
        plt.show()

    def assertion_fft(self):
        assert(self.size > 0)

    def assertion_ifft(self):
        assert(self.ifft_arr.__len__() is not 0)

    def FFT(self, size):
        try:
            assert(self.arr.__len__() != 0)
            self.fft_arr = np.fft.rfft(self.arr[: self.size])
            # self.fft_arr = np.fft.fftshift(self.fft_arr)
            self.ifft_arr = []
            self.freqs = np.linspace(0, self.sample_rate / 2, size / 2 + 1)
        except Exception as e:
            print('a time array expected')
        finally:
            return self.fft_arr

    def draw_freq(self, color=None, title=None):
        try:
            self.assertion_fft()
            tmp = 20 * np.log10(np.clip(np.abs(self.fft_arr), 1e-20, 1e100))
            self.draw(tmp, base=self.freqs, color=color, title=title)
        except Exception as e:
            print(self.fft_arr.__len__())
            print(e)

    def IFFT(self):
        try:
            self.assertion_fft()
            self.ifft_arr = np.fft.ifft(self.fft_arr)
        except Exception as e:
            print('a frequency array expected')
        finally:
            return self.ifft_arr

    def draw_time(self, xlim=None, ylim=None, color=None, title=None):
        try:
            self.assertion_ifft()
            self.draw(self.ifft_arr, xlim, ylim, color, title=title)
        except Exception as e:
            print('a time array expected')

if __name__ == '__main__':
    freq = Analyse()
    sample_rate = 8000
    size = 512
    arr = np.arange(0, 1.0, 1.0 / sample_rate)
    x = np.sin(2 * np.pi * 156.25 * arr) + 2 * np.sin(2 * np.pi * 234.375 * arr)
    freq.update(x, arr[: size], sample_rate, size)
    freq.draw()
    freq.FFT(size)
    freq.draw_freq(color='red')
