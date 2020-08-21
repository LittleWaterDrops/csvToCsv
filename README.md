# csvToCsv
remake csvToCsv / 기존 것 폭파 후 다시 만듦

conversion csv to csv by wanted format. It's work to data select.

This is used at Project_Data in my other repository.

It used as convert csv to txt first, but my order wants to get csv.

So, this code works like data select. 

There is no example, so if you want it, please contect me!

Or please understand my code.

Thank you!

변환한 데이터는 클라이언트의 요구 사항에 따라 제작하였음.

to 2020.08.10 
                      
                      각 인터벌을 time.txt와 비교하여 xpos, ypos, zpos .txt 에서 알맞는 좌표값 찾아 대체함.
                      
                      가속도, 지자기, 자이로 센서의 x, y, z값 따로 출력
                      
                      와이파이 데이터는 사용하지 않음. 
                      
                      비콘 데이터에서 major가 1이고 minor가 200-260 사이만 RSSI 값 출력

2020.08.11
                       
                       기존에 변환한 파일들 빈칸에 띄어쓰기 넣어지는 오류 해결. 
                      
                      major가 1이지만 minor가 200-260 사이가 아닌 값들도 출력되는 오류 해결.
                     

2020.08.21
                       
                       속도 값 추가.
                     
