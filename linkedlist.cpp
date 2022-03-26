#include <fstream>
#include <iostream>
#include <string>
#include <utility>

using namespace std;

struct Student {
public:
    int id_stu{};
    string fst_name, lst_name, gentle;
    int bir_day{}, bir_month{}, bir_year{};
    string faculty, school;
    double gpa{};
    int stu_year{};

    void inputStudentInfo() {
        cout << "Please input your additional information below" << endl;
        cin >> id_stu;
        cin >> fst_name >> lst_name;
        cin >> gentle;
        cin >> bir_day >> bir_month >> bir_year;
        cin >> faculty;
        cin >> school;
        cin >> gpa;
        cin >> stu_year;
    }

    string getInfo() const {
        return "ID Student: " + to_string(id_stu) +
               "\nFirst name: " + fst_name +
               "\nLast name: " + lst_name +
               "\nGentle: " + gentle +
               "\nBirthday: " + to_string(bir_day) + "/" + to_string(bir_month) + "/" + to_string(bir_year) +
               "\nFaculty: " + faculty +
               "\nSchool: " + school +
               "\nGPA: " + to_string(gpa) +
               "\nStudy Year: " + to_string(stu_year) + "\n";
    }

};

struct Node {
    Student student;
    Node *next{};
};

class LinkedList {
private:
    Node *head{};

    bool check_position(int k) const {
        return !isEmptyList() && k >= 0;
    }

    template<typename T>
    void swap(T &a, T &b) {
        T tmp = a;
        a = b;
        b = tmp;
    }

    void sort_linked_list(bool (*compare)(const Node *, const Node *)) {
        for (Node *i = head; i != nullptr; i = i->next) {
            for (Node *j = i->next; j != nullptr; j = j->next) {
                if (compare(i, j)) {
                    swap(i->student, j->student);
                }
            }
        }
    }

    static bool sortByName(const Node *a, const Node *b) {
        if (a->student.lst_name > b->student.lst_name) {
            return true;
        } else if (a->student.lst_name < b->student.lst_name) {
            return false;
        } else {
            return a->student.fst_name > b->student.fst_name;
        }
    }

    static bool sortByGPA(const Node *a, const Node *b) {
        return a->student.gpa > b->student.gpa;
    }

public:
    enum SORT {
        NAME, GPA
    };

    LinkedList() = default;

    bool isEmptyList() const {
        return this->head == nullptr;
    }

    bool isFull() const {
        return !isEmptyList();
    }

    Node *getValue(int k) const {
        if (!check_position(k)) {
            return nullptr;
        }
        Node *tmp = head;
        for (int i = 0; tmp != nullptr && i < k; ++i) {
            tmp = tmp->next;
        }
        return tmp;
    }

    void removeItem(int k) {
        Node *tmp, *p;
        if (k == 0) {
            p = head;
            head = head->next;
        } else {
            tmp = getValue(k - 1);
            if (tmp == nullptr || tmp->next == nullptr) {
                return;
            }
            p = tmp->next;
            tmp->next = p->next;
        }
        free(p);
    }

    void addItem(Student student, int k) {
        Node *tmp, *p = new Node;
        p->student = std::move(student);
        if (k == 0) {
            p->next = head;
            head = p;
        } else {
            tmp = getValue(k - 1);
            if (tmp == nullptr || tmp->next == nullptr) {
                return;
            }
            p = tmp->next;
            tmp->next = p;
        }
    }

    void addItem(Student student) {
        Node *tmp = head, *p = new Node;
        p->student = std::move(student);
        if (head == nullptr) {
            head = p;
        } else {
            for (; tmp->next != nullptr; tmp = tmp->next);
            tmp->next = p;
        }
    }

    string getListContext(int f, int t) const {
        Node *tmp = getValue(f);
        if (tmp == nullptr) return "";
        string result;
        for (int i = 0, len = t - f + 1; tmp != nullptr && i < len; ++i, tmp = tmp->next) {
            result += tmp->student.getInfo();
        }
        if (tmp == nullptr) return "Range invalid";
        return result;
    }

    string getListContext() const {
        Node *tmp = head;
        string result;
        for (; tmp != nullptr; tmp = tmp->next) {
            result += tmp->student.getInfo() + "\n";
        }
        return result;
    }

    int findingItem(Node *p) const {
        Node *tmp = head;
        int index = 0;
        while (tmp != nullptr) {
            if (tmp == p)
                return index;
            ++index;
            tmp = tmp->next;
        }
        return -1;
    }

    void sortList(SORT sort) {
        switch (sort) {
            case NAME: {
                sort_linked_list(sortByName);
                break;
            }
            case GPA: {
                sort_linked_list(sortByGPA);
                break;
            }
            default:
                break;
        }
    }


};

void inputHandle(LinkedList &list) {
    ifstream input("D:\\Algorithms and Data Structures\\input.txt", ios::in);
    while (!input.eof()) {
        Student a{};
        input >> a.id_stu;
        input >> a.fst_name >> a.lst_name;
        input >> a.gentle;
        input >> a.bir_day >> a.bir_month >> a.bir_year;
        input >> a.faculty;
        input >> a.school;
        input >> a.gpa;
        input >> a.stu_year;
        list.addItem(a);
    }
    input.close();
}

void outputHandle(LinkedList list) {
    fstream output("D:\\Algorithms and Data Structures\\output.txt", ios::out);
    output << list.getListContext();
    output.close();
}

int main() {
    LinkedList list{};
    inputHandle(list);
    Student test{};
//    test.inputStudentInfo();
    list.removeItem(2);
    list.addItem(test);
    list.sortList(LinkedList::NAME);

    list.addItem(test, 1);
    list.getListContext(0, 1);
    list.getValue(1);

    outputHandle(list);
}




