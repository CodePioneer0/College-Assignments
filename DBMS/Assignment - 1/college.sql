show tables;
DROP TABLE IF EXISTS crs_regd;
DROP TABLE IF EXISTS crs_offrd;
DROP TABLE IF EXISTS faculty;
DROP TABLE IF EXISTS students;
DROP TABLE IF EXISTS depts;
create table depts(
    deptcode varchar(3) primary key,
    deptname varchar(30) not null
);
CREATE TABLE students (
    rollno INT PRIMARY KEY,
    name varchar(30),
    bdate date check (bdate < '1997-01-01'),
    deptcode varchar(3),
    hostel int check (hostel < 10),
    parent_inc decimal(8,1),
    FOREIGN KEY (deptcode) REFERENCES depts(deptcode) ON DELETE CASCADE
);
create table faculty(
    fac_code varchar(8) primary key,
    fac_name varchar(30) not null,
    fac_dept varchar(3),
    foreign key (fac_dept) references depts(deptcode)
);
create table crs_offrd(
    crs_code varchar(5) primary key,
    crs_name varchar(35) not null,
    crs_credits decimal(2,1),
    crs_fac_cd varchar(8),
    foreign key (crs_fac_cd) references faculty(fac_code)
);
create table crs_regd(
    crs_rollno int,
    crs_cd varchar(5),
    marks decimal(5,2),
    primary key(crs_rollno, crs_cd),
    foreign key (crs_rollno) references students(rollno),
    foreign key (crs_cd) references crs_offrd(crs_code)
);

select *from depts;
select *from students;
select *from faculty;
select *from crs_offrd;
select *from crs_regd;

--Assignment 1
insert into students values(92005010,'John Doe','2000-05-15','CSE',1,50000);
delete from students where deptcode = 'CSE';
select faculty.fac_code, faculty.fac_name, crs_offrd.crs_code, crs_offrd.crs_name, crs_offrd.crs_credits
from faculty JOIN
crs_offrd ON faculty.fac_code = crs_offrd.crs_fac_cd where faculty.fac_name = 'Dr. NLS' or faculty.fac_name = 'Dr. DBP';

select faculty.fac_code, faculty.fac_name, faculty.fac_dept, crs_offrd.crs_code, crs_offrd.crs_name, crs_offrd.crs_credits
from faculty
JOIN
crs_offrd ON faculty.fac_code = crs_offrd.crs_fac_cd where faculty.fac_name = 'Dr. DBP';
select crs_name,crs_credits from crs_offrd where crs_credits between 4.0 and 6.0;
select crs_name , crs_credits from crs_offrd where crs_credits>6.5;

--Assignment 2

select count(*) from students where deptcode = 'CSE';
select crs_cd,min(marks) as MinMarks,max(marks) as MaxMarks,avg(marks) as AvgMarks from crs_regd group by crs_cd;

select crs_rollno,sum(crs_credits) as total_credit from crs_offrd
join crs_regd on crs_offrd.crs_code = crs_regd.crs_cd group by crs_rollno;

select hostel , count(*) as cse_students from students where deptcode = 'CSE' group by hostel;

select rollno,hostel,parent_inc from students as s where parent_inc = (select max(parent_inc) from students where hostel = s.hostel);


select name , parent_inc from students where parent_inc >(select parent_inc from students where rollno = 92005010);

select * from crs_regd where (crs_cd = 'CH103' and marks > (select marks from crs_regd where crs_rollno = 92005102 and crs_cd = 'CH103'))
UNION
select * from crs_regd where (crs_cd = 'PH106' and marks > (select marks from crs_regd where crs_rollno = 92005102 and crs_cd = 'PH106'));

--Assignment 3
select rollno,name,deptcode from students
join crs_regd on students.rollno = crs_regd.crs_rollno
where crs_cd = 'EE101';

select rollno,name from students
join crs_regd on students.rollno = crs_regd.crs_rollno
where deptcode = 'ELE' and crs_cd = 'EE101';

select rollno,name from students 
join crs_regd on students.rollno = crs_regd.crs_rollno
where deptcode = 'ELE' and rollno not in (select crs_rollno from crs_regd where crs_cd = 'EE101');

select name from students
join crs_regd on crs_regd.crs_rollno = students.rollno
join crs_offrd on crs_regd.crs_cd = crs_offrd.crs_code
where crs_name in ('DBMS','OS')
group by rollno
having count(DISTINCT crs_name) = 2;


select fac_name from faculty
join crs_offrd on faculty.fac_code = crs_offrd.crs_fac_cd
where crs_name = 'MIS'
UNION
select fac_name from faculty
join crs_offrd on faculty.fac_code = crs_offrd.crs_fac_cd
where crs_name = 'Software Engg.';

select fac_name from faculty
join crs_offrd on faculty.fac_code = crs_offrd.crs_fac_cd
where crs_name = 'MIS'
EXCEPT
select fac_name from faculty
join crs_offrd on faculty.fac_code = crs_offrd.crs_fac_cd
where crs_name = 'Software Engg.';

select name,hostel from students
where rollno not in (select crs_rollno from crs_regd);

select rollno,name,deptcode from students
where deptcode = 'ELE'
UNION
select rollno,name,deptcode from students
join crs_regd on students.rollno = crs_regd.crs_rollno
where crs_cd = 'CS101';

select rollno,name,deptcode from students
join crs_regd on students.rollno = crs_regd.crs_rollno
group by rollno having count(crs_cd) = (select count(*) from crs_offrd); 

update crs_regd
set marks = marks + 5
where crs_cd = (select crs_code from crs_offrd where crs_name = 'DBMS') and marks < 50;
