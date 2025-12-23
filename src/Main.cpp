#include <iostream>
#include "../include/Logger.h"
#include "../include/AuthManag.h"
#include "../include/CourseManag.h"
#include "../include/AttendanceManager.h"
#include "../include/ExamManager.h"
#include "../include/LibraryManager.h"

int main() {
    Logger log; log.init("../logs/scms.log");
    AuthManager auth(&log);
    CourseManager courses(&log);
    AttendanceManager att(&log);
    ExamManager exams(&log);
    LibraryManager library(&log);

    int ch;
    User* user = nullptr;

    while(true) {
        if(!user) {
            std::cout << "\n--- SCMS ---\n1.Login 2.Register 3.Exit: "; 
            if(!(std::cin >> ch)) { std::cin.clear(); std::cin.ignore(999,'\n'); continue; }
            if(ch==1) user = auth.login();
            else if(ch==2) auth.registerUser();
            else if(ch==3) break;
        } else {
            std::cout << "\nUser: " << user->getName() << "\n";
            std::cout << "1.Profile 2.Courses 3.Enroll 4.Att(Mark) 5.Exam(Sch) 6.Lib(List) 7.Lib(Issue) 8.Lib(Add) 0.Logout: ";
            if(!(std::cin >> ch)) continue;

            try {
                if(ch==1) user->printProfile();
                else if(ch==2) courses.listCourses();
                else if(ch==3) { std::string i; std::cout << "CID: "; std::cin >> i; courses.enrollStudent(user->getUsername(), i); }
                else if(ch==4) { std::string c, u, d, s; std::cout << "C_ID User Date Status: "; std::cin >> c >> u >> d >> s; att.markAttendance(c, u, d, s); }
                else if(ch==5) { std::string c, d; int m; std::cout << "C_ID Date Max: "; std::cin >> c >> d >> m; exams.scheduleExam(c, d, m); }
                
                // Library Module
                else if(ch==6) library.listBooks();
                else if(ch==7) { 
                    std::string bid; std::cout << "BookID: "; std::cin >> bid; 
                    library.issueBook(bid, user->getUsername()); 
                }
                else if(ch==8) {
                    if(user->getRole() == "Admin") {
                        std::string i, t, a; int c;
                        std::cout << "ID Title Author Copies: "; std::cin >> i >> t >> a >> c;
                        library.addBook(i, t, a, c);
                    } else std::cout << "Admin Only.\n";
                }
                
                else if(ch==0) user = nullptr;
            } catch(const std::exception& e) {
                std::cout << "[ERROR] " << e.what() << "\n";
            }
        }
    }
    log.close();
    return 0;
}
