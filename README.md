# endangered_pixels
Pixelates images based off remaining species population

This project was based off of a project I saw on reddit where and image of an endangered animal is
pixelated to include the same number of pixels as surviving members.

(imgur link)
https://imgur.com/gallery/NVNsyel

Sean Barett's stb_image and stb_image_write files (written in C) are used for image processing and writing

(Sean's stb github link. Its amazing check it out)
(https://github.com/nothings/stb)

For now only 8 and 24 bit .png files are supported but I am going to begin expanding to .jpg in the near future.
I also plan to create pixelating classes for each file type that can be extraced and used by anyone as they please.

I really hope you enjoy my project and please send any feedback you have my way.

Remeber all life is valuable and it is our duty to protect and preserve these beautiful creatures. 
Before you begin using this project I ask you consider making a donation to one of the various charities pretecting endagered animals
Below are links to various charities you can donate to. Thank you!

Wildlife Conservation Society
https://secure.wcs.org/donate/donate-and-help-save-wildlife?_ga=2.91736798.534069883.1570546862-1792404060.1570398503

Gorilla Doctors
gorilladoctors.org/donations/

Wildlife Alliance
https://www.wildlifealliance.org/donate/

World Wildlife Fund (**** much of the preexisting population info came from here ****)
https://support.worldwildlife.org/site/SPageServer?pagename=main_monthly&s_src=AWE1907OQ18299A01179RX&_ga=2.95384223.201006246.1570546969-730565520.1570391292

International Fund for Animal Welfare
https://www.ifaw.org/


RUNNING THE PROJECT:

Use included make file to run this project

When using your own image input please use only 8 or 24 bit .png images for now 
The population must also be smaller than the total number of pixels in the image
