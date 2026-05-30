#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;
struct Person
{
    int id;
    string name;
    /* data */
};
struct Student : public Person{
    double score;
    int age;
    string classID;
    int teacherid;
};
struct Teacher : public Person
{
    string course;
    /* data */
};
Student s;
Teacher t;
vector<Student> student;
vector<Teacher> teacher;
ostream& operator << (ostream& os,const Student& s){//学生信息
    os << "学号:" << s.id
    << " 姓名:" << s.name
    << " 年龄:" << s.age
    << " 成绩:" << s.score
    << " 班级:" << s.classID;
    return os;
}
ostream& operator << (ostream& os,const Teacher& t){//老师信息
    os << "老师ID:" << t.id 
    << " 老师姓名:" << t.name
    << " 授课名称:" << t.course;
    return os;
}
void Show(const Student& s){//合并输出学生和老师信息
    cout << s << endl;
    for(auto& t : teacher){
        if(t.id == s.teacherid){
            cout << " ↳" << t << endl;
            return;
        }
    }
    cout << " ↳ 无老师信息" << endl;
}
void SaveToFile(){//保存数据
    ofstream outFile("data.txt");
    if(!outFile){
        cout << "无法打开文件!" << endl;
        return;
    } 
    outFile << student.size() << endl;//记录有几条学生数据
    for(auto& s : student){
        outFile << s.id << " " << s.name << " " << s.age << " " << s.score << " " << s.classID
        << " " << s.teacherid << endl;
    }
    outFile << teacher.size() << endl;//记录有几条老师数据
    for(auto& t : teacher){
        outFile << t.id << " " << t.name << " " << t.course << endl;
    }
    outFile.close();
    cout << "数据已更新" << endl;
} 
void LoadToFile(){//加载数据
    ifstream inFile("data.txt");
    if(!inFile){
        cout << "暂无数据" << endl;
        return;
    }
    int count;
    inFile >> count;
    for(int i = 0;i < count;i++){//加载学生数据
        inFile >> s.id >> s.name >> s.age >> s.score >> s.classID >> s.teacherid; 
        student.push_back(s);
    }
    inFile >> count;
    for(int i = 0;i < count;i++){//加载老师数据
        inFile >> t.id >> t.name >> t.course; 
        teacher.push_back(t);
    }
    inFile.close();
    cout << "加载数据完毕!" << endl;
}
void Add(){
    cout << "-----增添信息-----" << endl;
    bool count = true;
    while(count){
        cout << "输入学生id " << "学生姓名 " << "学生年龄 " << "学生成绩 " << " 学生班级 " 
        << "老师id " << "老师的姓名 " << "老师授课名称 " << endl;
        cin >> s.id >> s.name >> s.age >> s.score >> s.classID >> t.id >>  t.name >> t.course;
        s.teacherid = t.id;
        student.push_back(s);
        bool found = false;
        for(int i = 0;i < teacher.size();i++){//判断老师信息存不存在
            if(teacher[i].id == t.id){
                found = true;
                break;
            }
        }
        if(!found) teacher.push_back(t);
        while(1){
            cout << "是否还要录入 y/n" << endl;
            char c;
            cin >> c;
            if(c == 'n') count = false;
            if(c == 'y' || c == 'n') break;
            else cout << "请输入正确的指令!!!!!" << endl;
        }
    }
    SaveToFile();
}
void Delete(){
    cout << "输入及格分:" << endl;
    int x;
    cin >> x;
    bool found = false;
    for(int i = student.size() - 1;i >= 0;i--){//删除不及格的学生
        int y = student[i].score;
        if(y < x){
            student.erase(student.begin() + i);
            found = true;
        }
    }
    if(found){
        for(int i = teacher.size() - 1;i >= 0;i--){//删除没有学生的老师
        bool count = false;
        for(int j = 0;j < student.size();j++){
            if(teacher[i].id == student[j].teacherid){
                count = true;
                break;
            }
        }
        if(!count) teacher.erase(teacher.begin() + i);
    }
        cout << "删除完成" << endl;
        SaveToFile();
    }
    else cout << "没有不及格的学生" << endl;
}
void ShowStudent(){
    cout << "输入想查看学生的id:" << endl;
    int x;
    cin >> x;
    int found = false;
    for(int i = 0;i < student.size();i++){
        if(x == student[i].id){
            Show(student[i]);
            found = true;
        }
    }
    if(!found){
        cout << "输入的学生id不对,请重新输入" << endl;
        ShowStudent();
    }
}
void ShowAll(){
    for(auto& s : student){
        Show(s);
    }
}
int main(int argc, char const *argv[])
{
    cout << "------------" << endl;
    cout << "学生管理系统" << endl;
    cout << "------------" << endl;
    LoadToFile();
    int x;
    int count = true;
    while(count){
        cout << "1: 加入学生信息" << endl
        <<"2: 删除学生信息" << endl
        << "3: 查看某个学生信息" << endl
        << "4: 查看当前所有学生信息" << endl
        << "0: 退出程序" << endl;
        cout << "输入对应服务的数字:";
        cin >> x;
        switch(x){
            case 1 : Add(); break;
            case 2 : Delete(); break;
            case 3 : ShowStudent(); break;
            case 4 : ShowAll(); break;
            case 0 : count = false; break;
            default:
            cout << "你输入的数字暂时没有服务,请重新输入" << endl;
        }
    }
    /* code */
    return 0;
}