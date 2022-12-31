#include <iostream>
#include <fstream>


using namespace std;

struct Student {
public:
    string name, division, addr;
    int roll;
    Student(){

    }
    Student(string name, int roll, string division, string addr){
        this->name = name;
        this->roll = roll;
        this-> division = division;
        this->addr = addr;
    }
};

class Database{
    Student database[20];
    int entries = 0;

public:

    void add(){
        string name, division, addr;
        int roll;
        cout<<"Enter the name of the student :";
        cin>>name;
        cout<<"Enter the Division of the student :";
        cin>>division;
        cout<<"Enter the Address of the student :";
        cin>>addr;
        cout<<"Enter the Roll number of the student :";
        cin>>roll;
        database[entries++] = Student(name, roll, division, addr);
    }

    void display(){
        for (int i = 0; i < entries; i++) {
            cout<<(i+1)<<".\t"<<database[i].name<<"\t"<<database[i].division<<"\t"<<database[i].roll<<"\t"<<database[i].addr<<endl;
        }
    }

    void beautify(){
        cout<<"--------------------------------------------------------------------------------";
    }

    void search(string name){
        for(int i = 0; i < 20; i++){
            if(name == database[i].name){
                cout<<"Found at serial no. "+(i+1)<<endl;
            }
        }
    }

    void write(){
        ofstream writer("demo.txt");
        for (int i = 0; i < entries; i++) {
            writer<<database[i].name;
            writer<<",";
            writer<<database[i].roll;
            writer<<",";
            writer<<database[i].division;
            writer<<",";
            writer<<database[i].addr;
            writer<<'|';
            writer<<"\n";

        }
        writer.close();
    }

    void read(){
        string name, division, addr;
        int roll;
        char temp[200],temp2[200];
        int count = 0;int j = 0;
        int object = 0;
        ifstream reader("demo.txt");
        while(reader>>temp){
            for (int i = 0; temp[i] != '\0' ; i++) {
                if (temp[i] == '|'){
                    temp2[j] = '\0';
                    addr = temp2;
                    count = 0;
                    j = 0;
                    database[object++] = Student(name, roll, division, addr);
                    break;
                }
                else if (temp[i] == ','){
                    temp2[j] = '\0';
                    switch (count) {
                        case 0:
                            name = temp2;
                            count++;
                            j = 0;
                            break;
                        case 1:
                            sscanf(temp2, "%d", &roll);
                            count++;
                            j = 0;
                            break;
                        case 2:
                            division = temp2;
                            count++;
                            j = 0;
                            break;
                    }
                } else{
                    temp2[j++] = temp[i];
                }
            }
        }
        entries = object;
    }


    int deleteEntry(string key){
        bool successful = false;
        for (int i = 0; i < entries; i++) {
            if (database[i].name == key){
                int j = i;
                while (j+1 < entries){
                    database[j] = database[j+1];
                    j++;
                }
                entries--;
                successful = true;
            }
        }

        if (successful){
            write();
            return 1;
        } else{
            return 0;
        }
    }


    void runApp(){
        read();
        string temp;
        int input = -1;
        while (input != 0){
            cout<<"1. Add\n";
            cout<<"2. Display\n";
            cout<<"3. Delete a record\n";
            cout<<"4. Search\n";
            cin>>input;
            switch (input) {
                case 1:
                    add();
                    write();
                    break;
                case 2:
                    display();
                    break;
                case 3:
                    string name;
                    cout<<"Enter the name of the student to be deleted :";
                    cin>>name;
                    if (deleteEntry(name) == 1){
                        cout<<"Record deleted successfully!"<<endl;
                    } else{
                        cout<<"Record not found!"<<endl;
                    }
                    break;
            }
        }
    }
};
int main() {
    Database database;
    database.runApp();
    return 0;
}
