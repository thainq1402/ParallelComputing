# ParallelComputing

Parallel Computing project MI4364

https://github.com/thainq1402/ParallelComputing

# Nhóm 27

| Tên              | MSSV     |
| ---------------- | -------- |
| Vũ Văn Nghĩa     | 20206205 |
| Trần Minh Quang  | 20206209 |
| Nguyễn Quốc Thái | 20206168 |

# I. YÊU CẦU

## A. Thực hiện chung (tất cả các nhóm): Thực hiện bài nhân ma trận với vector trên OpenMP, thử nghiệm với các kích thước khác nhau trong bài thực hành, in kết quả vào bài báo cáo. Đọc hiểu từng đoạn code.

## B. Thực hiện từng đề bài riêng.

### 1. NHÓM thực hiện theo đúng số thứ tự bài được giao

### 2. Bài tập lập trình có thể được thực hiện trên 2 nền tảng Windows, Linux

### 3. Viết chương trình tuần tự và song song với OpenMP, đưa ra kết quả so sánh với bộ dữ liệu với kích thước khác nhau

### 4. In code OpenMP trong bài báo cáo + kết quả chạy với dữ liệu kích thước khác nhau, số lượng luồng khác nhau...

### 5. Hình thức báo cáo theo nhóm, có thể hỏi đáp một số câu hỏi liên quan

# II. ĐỀ BÀI

## ĐỀ 2. Viết chương trình tính tích vô hướng của 2 vecto. (Dùng hàm thời gian so sánh với lập trình tuần tự)

<!-- Họp lần 1 ngày 20/11/2023 -->





#vector

vvn20206205@DESKTOP-7BPL48I MINGW64 ~/Desktop/VideoVN/content (main)
$      cd "/c/Users/vvn20206205/Downloads/" && g++ -fopenmp -std=c++17 main.cpp -o main && "/c/Users/vvn20206205/Downloads/"main
The sizes of the 2 vectors are: 10
Sequential programming: result = 16819.9, time = 0 microseconds
Parallel: thread = 2, result = 16819.9, time = 251 microseconds, efficiency = 0
Parallel: thread = 3, result = 16819.9, time = 194 microseconds, efficiency = 0
Parallel: thread = 4, result = 16819.9, time = 158 microseconds, efficiency = 0
Parallel: thread = 5, result = 16819.9, time = 233 microseconds, efficiency = 0
Parallel: thread = 6, result = 16819.9, time = 191 microseconds, efficiency = 0
Parallel: thread = 7, result = 16819.9, time = 158 microseconds, efficiency = 0
Parallel: thread = 8, result = 16819.9, time = 257 microseconds, efficiency = 0

vvn20206205@DESKTOP-7BPL48I MINGW64 ~/Downloads
$      cd "/c/Users/vvn20206205/Downloads/" && g++ -fopenmp -std=c++17 main.cpp -o main && "/c/Users/vvn20206205/Downloads/"main
The sizes of the 2 vectors are: 100
Sequential programming: result = 218418, time = 0 microseconds
Parallel: thread = 2, result = 218418, time = 226 microseconds, efficiency = 0
Parallel: thread = 3, result = 218418, time = 154 microseconds, efficiency = 0
Parallel: thread = 4, result = 218418, time = 198 microseconds, efficiency = 0
Parallel: thread = 5, result = 218418, time = 159 microseconds, efficiency = 0
Parallel: thread = 6, result = 218418, time = 177 microseconds, efficiency = 0
Parallel: thread = 7, result = 218418, time = 191 microseconds, efficiency = 0
Parallel: thread = 8, result = 218418, time = 214 microseconds, efficiency = 0

vvn20206205@DESKTOP-7BPL48I MINGW64 ~/Downloads
$      cd "/c/Users/vvn20206205/Downloads/" && g++ -fopenmp -std=c++17 main.cpp -o main && "/c/Users/vvn20206205/Downloads/"main
The sizes of the 2 vectors are: 1000
Sequential programming: result = 2.51013e+06, time = 3 microseconds
Parallel: thread = 2, result = 2.51013e+06, time = 211 microseconds, efficiency = 0.007109
Parallel: thread = 3, result = 2.51013e+06, time = 156 microseconds, efficiency = 0.00641026
Parallel: thread = 4, result = 2.51013e+06, time = 192 microseconds, efficiency = 0.00390625
Parallel: thread = 5, result = 2.51013e+06, time = 242 microseconds, efficiency = 0.00247934
Parallel: thread = 6, result = 2.51013e+06, time = 232 microseconds, efficiency = 0.00215517
Parallel: thread = 7, result = 2.51013e+06, time = 213 microseconds, efficiency = 0.00201207
Parallel: thread = 8, result = 2.51013e+06, time = 234 microseconds, efficiency = 0.00160256

vvn20206205@DESKTOP-7BPL48I MINGW64 ~/Downloads
$      cd "/c/Users/vvn20206205/Downloads/" && g++ -fopenmp -std=c++17 main.cpp -o main && "/c/Users/vvn20206205/Downloads/"main
The sizes of the 2 vectors are: 10000
Sequential programming: result = 2.48332e+07, time = 32 microseconds
Parallel: thread = 2, result = 2.48332e+07, time = 239 microseconds, efficiency = 0.0669456
Parallel: thread = 3, result = 2.48332e+07, time = 151 microseconds, efficiency = 0.0706402
Parallel: thread = 4, result = 2.48332e+07, time = 140 microseconds, efficiency = 0.0571429
Parallel: thread = 5, result = 2.48332e+07, time = 160 microseconds, efficiency = 0.04
Parallel: thread = 6, result = 2.48332e+07, time = 158 microseconds, efficiency = 0.0337553
Parallel: thread = 7, result = 2.48332e+07, time = 133 microseconds, efficiency = 0.0343716
Parallel: thread = 8, result = 2.48332e+07, time = 116 microseconds, efficiency = 0.0344828

vvn20206205@DESKTOP-7BPL48I MINGW64 ~/Downloads
$
