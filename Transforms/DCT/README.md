# DCT - Discrete Cosine Transform
Exercise inspired by Wikipedia's [JPEG codec example](https://en.wikipedia.org/wiki/JPEG#JPEG_codec_example).

The console app prints the hard-coded subimage array 
  taken from the wikipedia article. It then shifts the 
  values from [0, 255] to zero-centered range [-128, 127],
  performs DCT on this and prints the result.
  Copy of the output is in the file [dct-console-output.txt](.\dct-console-output.txt), and
  the result is comparable with the [example image](https://wikimedia.org/api/rest_v1/media/math/render/svg/46ee57df2a309dd59e0a10c9ab83e8b86d712e3e) from
[JPEG - Wikipedia](https://en.wikipedia.org/wiki/JPEG#Discrete_cosine_transform) (retrieved 29.8.2024).

