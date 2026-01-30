@echo off
set input="D:\Desktop\概率论.pdf"
set output="D:\Desktop\电子书&课件\离散数学\概率论.pdf"

ocrmypdf --output-type pdf --deskew --rotate-pages -l chi_sim+eng+mathsym ^
--tesseract-config "D:\Desktop\电子书&课件\离散数学\math_config.config" ^
--tesseract-timeout 1800 --tesseract-pagesegmode 6 --tesseract-oem 3 ^
--remove-background --optimize 3 %input% %output%

pause