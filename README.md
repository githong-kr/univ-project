# Univ-Project
> 과거의 제가 진행했던 대학교 프로젝트들을 관리하고 설명하는 공간입니다 🥲

<br />

# 과목 목록
## 1. 시스템 프로그래밍
## 2. 컴퓨터 네트워크
## 3. 컴퓨터 보안

<br />

# 과목 상세
## 1. 시스템 프로그래밍
### 1) hw1. simple programming.hwp
> 📅 2015.09.15.
- 사용자로부터 입력된 값의 유형을 판단하는 간단한 C 프로그램입니다.
- 분류해야 하는 값의 유형은 아래와 같습니다.
```
1. 숫자일 경우
2. 숫자를 제외한 알파벳일 경우
3. 숫자와 문자가 섞여있거나 특수문자가 있을 경우
4. 공백이 포함될 경우
5. 소숫점이 포함된 실수일 경우
```
---
### 2) hw2. hoc1 programming.pdf
> 📅 2015.10.03.
- linux mint OS 설치 후 lex & yacc 를 통해 간단한 계산기를 구현합니다.
- 기능 구현의 순서는 아래와 같습니다.
```
1. 사용자가 입력한 내용을 그대로 출력합니다.
2. 문자로만 혹은 숫자로만 이루어진 케이스를 판단하여 출력합니다.
3. 미리 정의된 문자열이 입력될 경우 케이스에 맞는 내용을 출력합니다.
4. 숫자를 나타내는 영어 단어가 입력될 경우 그에 맞는 숫자를 출력합니다.
5. unary plus 와 unary minus 연산을 문법에 추가합니다.
6. mod 연산자를 추가합니다.
7. 오류가 발생하더라도 프로그램이 종료되지 않도록 수정합니다.
8. 약수의 개수를 계산하는 연산자를 추가합니다.
```
---
### 3) hw3. hoc2, hoc3 programming.hwp
> 📅 2015.10.
- 기존에 구현했던 hoc1 프로그램에 기능을 덧붙여가는 내용입니다.
- 기능 구현의 순서는 아래와 같습니다.
```
1. 전위/후위 증감 연산자를 추가합니다.
2. ";" 문자를 구분자로 사용하여 한 줄에 여러 명령을 할 수 있도록 수정합니다.
3. 최종 연산의 결과를 저장하는 ans 변수를 추가합니다.
4. 변수의 목록을 관리하는 table 의 탐색 알고리즘을 구현합니다. ( Chaining Hash Table Structure )
5. 미리 선언된 상수를 추가합니다. ( PI 등 )
6. rand() 함수를 직접 구현해보는 방법을 고민합니다.
  - micro second 를 사용하기 => 빠르게 사용할 경우 중복된 난수 발생
  - 변수 선언 시 할당되는 메모리 주소값 사용하기 => 일부 국한된 범위 내에서 난수 발생
  - micro second + 메모리 주소값 함께 사용하기 => 메모리가 할당되는 규칙이 있어 결국 중복된 난수 발생
  - seed 값을 선언하고 시간에 따라 변화를 주며 사용하기 => 결국 규칙이 반복되어 중복된 난수 발생
  - 미리 정의된 난수표를 활용하는 방법 사용
```
---
### 4) hw4. rate programming.pdf
> 📅 2015.10.
- 저수준/고수준 입출력 함수를 활용하여 특정 파일 내 알파벳 별 비율을 계산하는 내용입니다.
- 기능 구현의 순서는 아래와 같습니다.
```
1. 저수준의 입출력을 사용
  - open(), close(), read(), write()
2. 고수준의 입출력을 사용
  - fopen(), fclose(), fgetc(), fprintf()
3. lex를 사용
  - yyin, yyout, yylex()
```
---
### 5) hw5. ll programming.pdf
> 📅 2015.10.
- 리눅스 쉘에서의 ls -laR [경로] 기능을 직접 구현하는 내용입니다.
- 기능 구현의 순서는 아래와 같습니다.
```
1. [경로] 부분은 매개변수로 받아 처리합니다.
2. 해당 경로 내 파일 목록을 리스트에 오름차순으로 추가합니다.
3. 리스트의 내용(moide, link, uid, gid, size, time, name)을 순서대로 출력합니다.
4. 리스트의 내용이 디렉토리일 경우 1~3 과정을 재귀적으로 반복합니다.
```
---
### 6) hw6. simple shell programming.pdf
> 📅 2015.11.05.
- mysh 이라는 이름의 간단한 쉘을 구현하는 내용입니다.
- 기능 구현의 순서는 아래와 같습니다.
```
1. 현재 디렉토리 경로를 표시합니다.
2. 입력받은 문자열을 토큰화하여 자식 프로세스가 실행할 수 있도록 합니다.
3. 실행된 명령들은 시간과 함께 log 를 남깁니다.
4. 자식 프로세스가 종료될 때까지 부모 프로세스는 대기하도록 합니다.
5. cd 명령어를 구현합니다.
```
### 7) hw7. IPC programming.pdf
> 📅 2015.11.17.
- 프로세스 간 데이터를 주고받는 기능을 구현하기 위한 여러 가지 방법에 대한 내용입니다.
- 기능 구현의 순서는 아래와 같습니다.
```
1. 메모리 매핑 방식, 파이프 방식을 활용합니다.
2. UNIX System V 에서 제공하는 Message Queue 방식, Shared Memory 방식을 활용합니다.
3. 네트워크 통신 방식을 활용합니다.
```
### 8) Project Euler.pdf
> 📅 2015.11.26.
- Project Euler 의 145번, 173번, 179번 문제의 풀이입니다.
### 9) Term Project1. hoc program.pdf
> 📅 2015.11.17.
- 앞서 개발한 hoc 프로그램의 최종 버전 내용입니다.
### 10) Term Project2. archive report.pdf
> 📅 2015.11.30.
- 앞서 개발했던 내용들을 모은 내용입니다.
---
## 2. 컴퓨터 네트워크
### 1) Client Server Program
> 📅 2016.04.25.
- Server & Client 구조로 가위바위보를 할 수 있는 프로그램에 대한 내용입니다.
- 위 프로그램에 대한 기능 목록은 아래와 같습니다
```
1. CvP(Computer vs Player) 모드와 PvP(Player vs Player) 모드를 가집니다.
2. 멀티스레드 방식으로 여러 플레이어가 동시에 플레이할 수 있습니다.
3. 패킷은 직접 구현한 간단 알고리즘으로 암호화됩니다.
4. 사용자 등록 후 플레이 시, 전적이 관리됩니다.
5. 사용자 탐색 성능을 Chaining Hash Table 구조를 활용하여 개선합니다.
```
- 추가로 보드게임(다빈치코드)을 구현한 내용입니다.
---
### 2) Building A Small Network
> 📅 2016.06.06.
- 직접 소규모 네트워크를 구축해보는 내용입니다.
- 소규모 네트워크에 속한 서버 목록은 아래와 같습니다.
```
1. 가위바위보 Server
2. Mail Server
3. Web Server
4. DNS Server
5. FTP Server
6. DHCP Server
```
---
## 3. 컴퓨터 보안
### 1) homework
> 📅 2016.11.
- 교과서의 연습 문제 풀이 & 공인인증서 분석 & Snort 구축의 내용이 있습니다.
---
### 2) encryption algorithm
> 📅 2016.12.
- 직접 구현한 암호화 라이브러리입니다.
- 암호화 알고리즘의 종류는 아래와 같습니다.
```
1. A5_1
2. Caesar Cipher
3. ECC Diffie-Hellman
4. Feistel
5. RSA
6. SHA256
```
---
### 3) project
> 📅 2016.12.
- Online Banking System 을 보안 관점에서 구현한 내용입니다.
---