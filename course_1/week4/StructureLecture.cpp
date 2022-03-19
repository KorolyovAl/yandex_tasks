#include <iostream>
#include <string>
using namespace std;

struct Specialization {
	  string name;
	  explicit Specialization (string new_name) {
		  name = new_name;
	  }
};

struct Course {
	  string name;
	  explicit Course (string new_name) {
		  name = new_name;
	  }
};

struct Week {
	  string name;
	  explicit Week (string new_name) {
		  name = new_name;
	  }
};

struct LectureTitle {
  string specialization;
  string course;
  string week;

  LectureTitle (Specialization new_specialization, Course new_course, Week new_week) {
	  specialization = new_specialization.name;
	  course = new_course.name;
	  week = new_week.name;
  }
};

void PrintLectureTitle (const LectureTitle& lecture) {
	cout << lecture.specialization << " " << lecture.course << " " << lecture.week << endl;
}

int main() {

	LectureTitle title(
	    Specialization("C++"),
	    Course("White belt"),
	    Week("4th")
	);

	return 0;
}
