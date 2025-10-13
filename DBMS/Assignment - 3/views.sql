--Assignment Sheet 3
create view cse_stud as select rollno, name, hostel from students where deptcode = 'CSE';
select *from cse_stud;
insert into cse_stud values(92005120,'Amit Kumar',3);
--The view does not show the new data, but the original database has it with values as NULL not present in view

update students set parent_inc = parent_inc + 5000;
select *from cse_stud;

drop view cse_stud;

create view mech_stud as
select rollno,name,deptcode,year(curdate())-year(bdate) as age
from students
where deptcode = 'MEC';

insert into students values(92005121,'Ravi Shankar','1995-05-12','MEC',2,15000);
select *from mech_stud;

delete from students where name = 'Ravi Shankar';
select *from mech_stud;

update students set deptcode = 'CSE' where name = 'Manoj';