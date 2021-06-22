# DiscretedMath
**Bài tập nhóm môn Toán rời rạc IT3022 - Thầy Trần Vĩnh Đức**
## **I.Thành viên:**
1. Đỗ Minh Quân - 20194651
2. Trương Minh Hồng - 20194576
3. Nguyễn Bá Thái - 20194666
## **II.Giới thiệu tổng quan**
Đây là bài tập nhóm môn Toán rời rạc, nội dung về các thuật toán trên đồ thị gồm duyệt đồ thị **(BFS, DFS)**, tìm đường đi ngắn nhất **(Dijsktra)**, cây khung nhỏ nhất **(Kruskal)**, thuật toán tham lam tô màu đồ thị **(Greedy Algorithm for Coloring Graph)**. 
## **III.Ngôn ngữ và các extensions sử dụng**
Ngôn ngữ được sử dụng là **C**, kèm theo cấu trúc dữ liệu [cây đỏ đen](http://web.eecs.utk.edu/~jplank/plank/classes/cs360/360/notes/Libfdr/) để xây dựng đồ thị. Cách xây dựng đồ thị bằng cây đỏ đen, vui lòng tham khảo [slide](https://users.soict.hust.edu.vn/hieunk/courses/IT3240E/lect06.pdf). Để visualize đồ thị, sử dụng [Graphviz](https://graphviz.org/about/).
## **IV.Demo chương trình**
Vui lòng xem [playlist](https://www.youtube.com/playlist?list=PL2-9WSG7DAvUtaesL58PTmWnnV59CiGn7).
## **V.Về chương trình**
### 1. Tô màu đồ thị (Greedy Algorithm)
Vào thư mục Coloring, thay đổi file source.txt (nếu cần xử lí đồ thị khác):
- Dòng đầu là 2 số nguyên v và e là số đỉnh và số cạnh.
- e dòng sau là các cạnh của đồ thị (gồm đỉnh bắt đầu và kết thúc).

Để chạy chương trình, vào terminal/cmd của bạn, cd đến thư mục Coloring và nhập lệnh sau:
>gcc -Ilibfdr -c coloring.c

>gcc -o main coloring.o libfdr\libfdr.a

>.\main

Chương trình sẽ xuất ra file target.txt. Để ra được file đồ thị PDF cần sử dụng câu lệnh:
>dot -Tpdf target.txt -o demo.pdf

Đồ thị được tô màu biểu diễn trong file demo.pdf.

### 2.Cây khung nhỏ nhất (MST)

Vào thư mục MST, thay đổi file dothi_source.txt (nếu cần xử lí đồ thị khác):
- Dòng đầu là 2 số nguyên v và e là số đỉnh và số cạnh.
- e dòng sau là các cạnh của đồ thị (gồm đỉnh bắt đầu, đỉnh kết thúc và **trọng số**).

Để chạy chương trình, vào terminal/cmd, cd đến thư mục MST và nhập lệnh sau:
>gcc -Ilibfdr -c MST.c

>gcc -o main MST.o weightedGraphlib.o libfdr\libfdr.a

>.\main

Tương tự như trên, chương trình xuất ra file demo_input.txt và demo_output.txt (file dot biểu diễn đồ thị gốc và cây khung nhỏ nhất của nó). Để ra được file PDF biểu diễn đồ thị và MST, sử dụng lệnh:
>dot -Tpdf demo_input.txt -o demo_input.pdf

>dot -Tpdf demo_output.txt -o demo_output.pdf

Đồ thị gốc và cây khung nhỏ nhất của nó được biểu diễn trong file demo_input.pdf và demo_output.pdf.

### 3.Duyệt, tìm đường đi (BFS, DFS, Dijsktra)

Vào thư mục Traverse, thay đổi file dothi_source.txt (nếu cần xử lí đồ thị khác):
- Dòng đầu là 2 số nguyên v và e là số đỉnh và số cạnh.
- e dòng sau là các cạnh của đồ thị (gồm đỉnh bắt đầu, đỉnh kết thúc và **trọng số**).

Tương tự để chạy, vào terminal/cmd, cd đến thư mục Traverse và nhập lệnh:
>gcc -Ilibfdr -c Traverse.c

>gcc -o main Traverse.o jlib.o libfdr\libfdr.a

>.\main

Chọn 1 trong 3 chức năng BFS, DFS, Dijsktra để chương trình thực hiện.







