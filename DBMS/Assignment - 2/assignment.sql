--Assignment Sheet 2
--Assignment 4
select name from students where name like 'S%r_';

select name,sum(marks) as total_marks from students
join crs_regd on students.rollno = crs_regd.crs_rollno
where deptcode = 'CSE' and bdate = (select max(bdate) from students where deptcode = 'CSE')
group by rollno;


select rollno,name,TIMESTAMPDIFF(YEAR,bdate,CURDATE()) as age from students;


--Assignment 5

select rollno,name,marks from students
join crs_regd on students.rollno = crs_regd.crs_rollno
join crs_offrd on crs_offrd.crs_code = crs_regd.crs_cd
where crs_name = 'DBMS' and marks = (select max(marks) from crs_regd
join crs_offrd on crs_regd.crs_cd = crs_offrd.crs_code where crs_name = 'DBMS' and marks<(select max(marks) from crs_regd join crs_offrd on crs_regd.crs_cd = crs_offrd.crs_code where crs_name = 'DBMS'));

select crs_code,crs_name , max(marks)-min(marks) as diff_marks
from crs_regd
join crs_offrd on crs_regd.crs_cd = crs_offrd.crs_code
group by crs_code,crs_name;

SELECT name
FROM students
JOIN crs_regd ON students.rollno = crs_regd.crs_rollno
JOIN crs_offrd ON crs_regd.crs_cd = crs_offrd.crs_code
JOIN faculty ON crs_offrd.crs_fac_cd = faculty.fac_code
GROUP BY students.name
HAVING COUNT(DISTINCT faculty.fac_dept) = (SELECT COUNT(*) FROM depts);

select rollno,name from students
where rollno not in (select distinct rollno from crs_offrd, faculty, crs_regd, students
where crs_fac_cd=fac_code
AND crs_cd=crs_code
AND crs_rollno=rollno
AND fac_dept!=deptcode
GROUP BY rollno
UNION
(select rollno from students except (select distinct crs_rollno from crs_regd)));


--Assignment 6
select name,parent_inc from students
where deptcode != 'ARC' and parent_inc < 12000
order by parent_inc desc;

select distinct s.parent_inc
from students as s
where s.hostel = 5 and 
5 = (select count(distinct p.parent_inc) from students as p
where p.hostel = 5 and p.parent_inc >= s.parent_inc);

select name,deptcode,rollno
from(select deptcode,rollno,name,sum(marks) as totalmarks
from students,crs_regd
where students.rollno=crs_regd.crs_rollno group by rollno) as tb1
where (deptcode,totalmarks) in (select deptcode,max(totalmarks) from (select deptcode,rollno,name,sum(marks) as totalmarks
from students,crs_regd
where students.rollno=crs_regd.crs_rollno group by rollno)as tb2 group by deptcode);
