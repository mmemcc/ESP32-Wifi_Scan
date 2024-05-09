## 사용법
해당 코드를 ESP32 모듈에 업로드 후 아래 매트랩 링크 폴더를 통째로 다운로드  
해당 폴더 내에 매트랩 앱 사용 설명서 참고  

## 매트랩 코드
V1: [https://drive.google.com/drive/folders/1zXymEdCSx9j-uesLY7W9gB2mRGxoH489?usp=sharing  ](https://drive.google.com/drive/folders/10aouw_EBh2GOeL8dMG2eUUXHceP9TmLP?usp=sharing)  
V2: https://drive.google.com/drive/folders/12BD8M4mJOrAFB87ioABmAVfyy1pw8_xL?usp=sharing  

### 설명 (아래부터 몰라도 됨)
부팅 후 시리얼 모니터에 'scan' 입력 시 wifi AP를 스캔함.  
맨 처음에 나오는 숫자: scan 된 wifi ap 수  
SSID    RSSI(dBm)    Channel    Band Width(MHz)  

### Example
I (635) main_task: Returned from app_main()  
scan> scan  
47  
chung1118,      -38,    5,      40  
chung1118(2),   -44,    11,     40  
[LG_CeilingCassette A/C]34f4,   -44,    11,     20  
sejong, -46,    1,      20  
eduroam,        -46,    1,      20  
sejong-help,    -48,    1,      20  
sejong-guest,   -48,    1,      20  
ip8004T1120_2G, -50,    4,      40  
T wifi zone,    -53,    1,      20  
T wifi zone_secure,     -53,    1,      20  
T Free WiFi Zone,       -53,    1,      20  
DS_LAB, -53,    9,      20  
TP-LINK_A414,   -54,    6,      40  
[LG_AirPurifier]1a81,   -55,    11,     20  
MTV310 DAD,     -57,    8,      40  
sungkyu,        -58,    3,      40  
1106A_Lab,      -58,    11,     20  
wf21010,        -59,    4,      40  
DIRECT-C4 C56x Series,  -62,    1,      20  
APTL,   -62,    5,      40  
[air purifier] Samsung, -68,    1,      20  

