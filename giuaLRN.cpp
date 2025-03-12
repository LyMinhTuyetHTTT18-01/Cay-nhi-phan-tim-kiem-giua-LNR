#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Cấu trúc lưu thông tin sinh viên
struct Student {
    string id;
    string name;
    int birthYear;
    double gpa;
};

// Cấu trúc của một nút trong BST
struct Node {
    Student data;
    Node* left;
    Node* right;
    Node(Student s) : data(s), left(nullptr), right(nullptr) {}
};

// Hàm chèn sinh viên vào BST theo mã sinh viên
Node* insert(Node* root, Student s) {
    if (!root) return new Node(s);
    if (s.id < root->data.id)
        root->left = insert(root->left, s);
    else
        root->right = insert(root->right, s);
    return root;
}

// Duyệt cây theo thứ tự giữa (LNR) và in thông tin sinh viên
void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    cout << "MSSV: " << root->data.id << ", Ho ten: " << root->data.name
         << ", Nam sinh: " << root->data.birthYear
         << ", Diem TB: " << root->data.gpa << endl;
    inorder(root->right);
}

// Đếm số node lá (node không có con)
int countLeafNodes(Node* root) {
    if (!root) return 0;
    if (!root->left && !root->right) return 1;
    return countLeafNodes(root->left) + countLeafNodes(root->right);
}

// Tìm kiếm sinh viên theo mã số
Node* search(Node* root, string id) {
    if (!root || root->data.id == id) return root;
    if (id < root->data.id)
        return search(root->left, id);
    else
        return search(root->right, id);
}

// Tìm sinh viên có điểm trung bình cao nhất
Node* findMaxGPA(Node* root, Node* &maxNode) {
    if (!root) return maxNode;
    if (!maxNode || root->data.gpa > maxNode->data.gpa)
        maxNode = root;
    findMaxGPA(root->left, maxNode);
    findMaxGPA(root->right, maxNode);
    return maxNode;
}

// Đọc danh sách sinh viên từ file và xây dựng BST
Node* readStudentsFromFile(string filename) {
    ifstream file(filename);
    if (!file) {
        cout << "Khong the mo file!" << endl;
        return nullptr;
    }
    Node* root = nullptr;
    Student s;
    while (file >> s.id) {
        file.ignore(); // Bỏ qua khoảng trắng
        getline(file, s.name);
        file >> s.birthYear >> s.gpa;
        root = insert(root, s);
    }
    file.close();
    return root;
}

// Hiển thị menu
void menu() {
    cout << "\n------ MENU ------" << endl;
    cout << "1. Hien thi danh sach sinh vien (LNR)" << endl;
    cout << "2. Tim kiem sinh vien theo MSSV" << endl;
    cout << "3. Tim sinh vien co diem trung binh cao nhat" << endl;
    cout << "4. Dem so node la trong cay" << endl;
    cout << "5. Thoat chuong trinh" << endl;
    cout << "_______________________\n";
}

// Hàm chính
int main() {
    Node* root = readStudentsFromFile("students.txt");

    if (!root) {
        cout << "Cay rong hoac khong the doc file!" << endl;
        return 0;
    }

    int choice;
    do {
        menu();
        cout << "Nhap lua chon: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                cout << "\nDanh sach sinh vien (LNR):" << endl;
                inorder(root);
                break;
            
            case 2: {
                string searchID;
                cout << "\nNhap MSSV can tim: ";
                cin >> searchID;
                Node* found = search(root, searchID);
                if (found)
                    cout << "Tim thay: " << found->data.name 
                         << ", Diem TB: " << found->data.gpa << endl;
                else
                    cout << "Khong tim thay sinh vien nay!" << endl;
                break;
            }

            case 3: {
                Node* maxGPAStudent = nullptr;
                findMaxGPA(root, maxGPAStudent);
                if (maxGPAStudent)
                    cout << "\nSinh vien co diem trung binh cao nhat: " 
                         << maxGPAStudent->data.name
                         << " (MSSV: " << maxGPAStudent->data.id 
                         << ", GPA: " << maxGPAStudent->data.gpa << ")" << endl;
                break;
            }

            case 4:
                cout << "\nSo node la trong BST: " << countLeafNodes(root) << endl;
                break;

            case 5:
                cout << "\nThoat chuong trinh!" << endl;
                break;

            default:
                cout << "Lua chon khong hop le! Vui long nhap lai." << endl;
        }

    } while (choice != 5);

    return 0;
}
