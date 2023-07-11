#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

std::map<std::string, float> c_letter_grades{{"A+",4.3},{"A",4.0},{"A-",3.7},
  {"B+",3.3},{"B",3.0},{"B-",2.7},{"C+",2.3},{"C",2.0},{"C-",1.7},{"D+",1.3},
  {"D",1.0},{"D-",0.7},{"F",0.0}};

void clearExtra()
{
  // ignores all of the characters up until newline
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

struct Course
{
  std::string m_name;
  int m_credits;
  float m_grade;
  void print()
  {
    std::cout << "-----------------\n";
    std::cout << "Course: " << m_name << '\n';
    std::cout << "Credit: " << m_credits << '\n';
    std::cout << "Grade: " << m_grade << '\n';
    std::cout << "-----------------\n";
  }
};


int prompt()
{
  int _entry{};
  std::cin >> _entry;
  if(std::cin.fail())
  {
    std::cin.clear();
    clearExtra();
  }
  clearExtra();
    
  return _entry;
}



void create_course(std::vector<Course>& list)
{
  Course _course{};
  std::string _temp_grade{};
  bool course_created{false};
  while(!course_created)
  {
    std::cout << "Enter course name: ";
    std::cin >> _course.m_name; clearExtra();
    std::cout << "Enter course credit: ";
    _course.m_credits = prompt();
    std::cout << "Enter course grade (ex: A+,B-,etc.): ";
    std::cin >> _temp_grade; clearExtra();

    std::map<std::string, float>::iterator _iter = c_letter_grades.find(_temp_grade);
    if(_iter != c_letter_grades.end())
    {
      _course.m_grade = c_letter_grades.at(_temp_grade);
      list.push_back(_course);
      course_created = true;
    }
    else
    {
      std::cerr << "ERROR: Wrong grade format entered, make sure you enter letter grade.\n";
    }
  }
}

void calculate_gpa(std::vector<Course>& list)
{
  float grade_points{};
  int total_credits{};
  float overall_GPA{};

  for(Course c : list)
  {
    total_credits += c.m_credits;
    grade_points += c.m_grade * c.m_credits;
  }
  
  overall_GPA = grade_points/total_credits;
  std::cout << "====================\n" <<"Overall GPA: " << overall_GPA
  << "\n====================\n";
}

void clear_All()
{
  std::cout << "Clear All \n";
}


int main()
{
  std::vector<Course> courses_list{};
  bool is_running = true;
  int m_option{};


  while(is_running)
  {
    std::cout << "Select operation:\n1.Add course" << "\n2.Calculate GPA"
    << "\n3.Clear" << "\n4.Exit\n";
    m_option = prompt();
    switch(m_option)
    {
      case 1:
        create_course(courses_list);
        std::cout << "=============================\n";
        for(Course c : courses_list)
        {
          c.print();
        }
        std::cout << "=============================\n";
        break;

      case 2: calculate_gpa(courses_list); break;
      case 3: clear_All(); break;
      case 4: is_running = false; break;
      default:
        std::cerr << "Error: Error\n"; break;
    }
  }
  return 0;
}
