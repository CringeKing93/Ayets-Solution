'Easy qsts(no relations needed)'

1 /*Get all enrolled students for a specific period,program,year ?*/
select c.contact_first_name, c.contact_last_name, s.*from students s
left join contacts c on c.contact_email = s.student_contact_ref
where s.student_population_year_ref = 2021 and s.student_population_code_ref = 'CS';
-- or
select * from students s where s.student_population_year_ref = 2021 and s.student_population_code_ref = 'CS';


2 /*Get number of enrolled students for a specific period,program,year*/
select count(1) from students s where s.student_population_year_ref = 2021 and s.student_population_code_ref = 'CS';

3 - /*Get All defined exams for a course from grades table*/
select c.course_code, g.grade_exam_type_ref from grades g
left join courses c on g.grade_course_code_ref = c.course_code
left join exams e on e.exam_course_code = c.course_code where c.course_code = 'PG_PYTHON';

4 - /*Get all grades for a student*/

select * from grades g where grade_student_epita_email_ref = 'marjory.mastella@epita.fr' and grade_score
select * from students s

select * from grades g
where grade_student_epita_email_ref = 'simona.morasca@epita.fr';


5 - /*Get all grades for a specific Exam*/
select * from grades g
where grade_course_code_ref = 'SE_ADV_JS'

6 - /*Get students Ranks in an Exam for a course*/
select * from grades
select g.grade_student_epita_email_ref, g.grade_course_code_ref, g.grade_score,
rank() over(order by g.grade_score desc) student_rank
from grades g
where g.grade_course_code_ref = 'SE_ADV_JS' and g.grade_exam_type_ref = 'Project';

7 - /*Get students Ranks in all exams for a course*/

select g.grade_student_epita_email_ref, g.grade_course_code_ref, g.grade_score, g.grade_exam_type_ref,
rank() over(order by g.grade_score desc) student_rank
from grades g
where g.grade_course_code_ref = 'DT_RDBMS';

8 - /*Get students Rank in all exams in all courses */
select g.grade_student_epita_email_ref, g.grade_course_code_ref, g.grade_score,
rank() over(partition by g.grade_course_code_ref order by g.grade_score desc) student_rank
from grades g;

9 - /*Get all courses for one program*/

select * from programs p
where program_assignment = 'SE';


10 - /*Get courses in common between 2 programs*/
select * from courses

select * from programs p
where program_course_code_ref in('DT_RDBMS', 'PG_PYTHON') and program_assignment in('CS', 'SE');


11 - /*Get all programs following a certain course*/
select program_assignment, program_course_code_ref from programs p
order by program_assignment;

12 - /*get course with the biggest duration*/
select * from courses
order by duration desc limit 2;

13 - /*get courses with the same duration*/
select * from courses c
where duration in('24', '11', '21')

-- or
select * from courses c where c.duration in(select c2.duration from courses c2 group by c2.duration having count(c2.duration) > 1) order by c.duration asc


14 - /*Get all sessions for a specific course*/
select * from sessions
where session_course_ref = 'PM_AGILE'

15 - /*Get all session for a certain period*/

select * from sessions s
where session_date in('2020-10-04', '2020-10-05', '2020-10-06', '2020-10-07', '2020-10-08')

16 - /*Get one student attendance sheet*/

select a.attendance_student_ref, a.attendance_presence from attendance a
where attendance_student_ref = 'kanisha.waycott@epita.fr';


17 - /*Get one student summary of attendance*/

select * from attendance a
where attendance_student_ref = 'kris.marrier@epita.fr'


18 - /*Get student with most absences*/
select * from attendance
select attendance_student_ref, attendance_presence from attendance a
order by attendance_presence asc



Hard questions(build the relations requiered)*/


1 - /*Get all exams for a specific Course*/
select * from exams 
where exam_course_code in ('CS_SOFTWARE_SECURITY', 'exam_type'); 


select e.exam_course_code, e.exam_weight, e.exam_type from exams e
where e.exam_course_code in 'SE_ADV_JAVA'


2 - /*Get all Grades for a specific Student*/
select * from grades
where grade_student_epita_email_ref  in ('kallie.blackwood@epita.fr', 'grade_score')
  
select c.contact_first_name,c.contact_last_name, g.grade_course_code_ref, g.grade_score from grades g
inner join students s on g.grade_student_epita_email_ref = s.student_epita_email 
inner join contacts c on s.student_contact_ref = c.contact_email 
where g.grade_student_epita_email_ref='kallie.blackwood@epita.fr'

3 - /*Get the final grades for a student on a specifique course or all courses*/
select * from courses
select * from grades


select g grade_student_epita_email_ref, grade_score from grades g  in ('albina.glick@epita.fr', 'DT_RDBMS', 'grade_score')


select s.student_epita_email ,g.grade_course_code_ref, sum(e.exam_weight * g.grade_score)/sum(e.exam_weight) from grades g 
inner join exams e on g.grade_course_code_ref = e.exam_course_code
inner join students s on g.grade_student_epita_email_ref =s.student_epita_email 
where s.student_epita_email ='kallie.blackwood@epita.fr' 
group by g.grade_course_code_ref, s.student_epita_email  


4 - /*Get the students with the top 5 scores for specific course*/
with total_grade_course as (
	select c.contact_first_name, c.contact_last_name ,g.grade_course_code_ref, sum(e.exam_weight * g.grade_score)/sum(e.exam_weight) as total_grade,
	rank() over (partition by g.grade_course_code_ref order by sum(e.exam_weight * g.grade_score)/sum(e.exam_weight) desc) as rnk
	from grades g 
	inner join exams e on g.grade_course_code_ref = e.exam_course_code
	inner join students s on g.grade_student_epita_email_ref = s.student_epita_email
	inner join contacts c on s.student_contact_ref = c.contact_email 
	group by g.grade_course_code_ref, c.contact_first_name, c.contact_last_name
)
select contact_first_name, contact_last_name, grade_course_code_ref, total_grade, rnk
from total_grade_course
where rnk <=5 and grade_course_code_ref ='DT_RDBMS'

5 - /*Get the students with the top 5 scores for specific course
per rank*/


6 - /*Get the Class average for a course*/
  
select g.grade_course_code_ref, (sum(e.exam_weight * g.grade_score)/sum(e.exam_weight)::float) as class_average
from grades g inner join exams e on g.grade_course_code_ref = e.exam_course_code
inner join students s on g.grade_student_epita_email_ref =s.student_epita_email 
group by g.grade_course_code_ref

--bonuses:
1 - /*Get a student full report of grades and attendances*/


2 - /*Get a student full report of grades, ranks per courseand attendances*/


Those questions are from easy to super hard
