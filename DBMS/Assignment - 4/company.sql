
CREATE TABLE DEPT (
    DEPTNO CHAR(4) PRIMARY KEY CHECK (DEPTNO LIKE 'D%'),
    DNAME VARCHAR(20) CHECK (DNAME IN ('Accounting', 'Sales', 'Research', 'Operations')),
    LOC VARCHAR(20)
);

CREATE TABLE EMP (
    EMPNO INT PRIMARY KEY CHECK (EMPNO BETWEEN 7000 AND 8000),
    ENAME VARCHAR(10) NOT NULL,
    JOB VARCHAR(10) CHECK (JOB IN ('Clerk','Salesman','Manager','Analyst','President')),
    MGR INT,
    HIREDATE DATE,
    SAL DECIMAL(10,2),
    COMM DECIMAL(10,2) DEFAULT 0 CHECK (COMM < 1500),
    DEPTNO CHAR(4),
    FOREIGN KEY (DEPTNO) REFERENCES DEPT(DEPTNO),
    FOREIGN KEY (MGR) REFERENCES EMP(EMPNO)
);

select dept.DNAME, max(SAL) - min(SAL) as Difference
from emp,dept
where emp.deptno = dept.deptno
group by dept.DEPTNO
order by Difference desc;

select A.EMPNO as employee_id, A.ENAME as employee_name, B.EMPNO as manager_id, B.ENAME as manager_name
from EMP A, EMP B
where A.MGR = B.EMPNO;

select TOTAL,TOTAL_2000
from
(select count(*) as TOTAL from EMP ) as tb1,
(select count(*) as TOTAL_2000 from EMP where HIREDATE between '2000-01-01' and '2000-12-31') as tb2;

select MGR as manager_id,min(SAL) as min_salary
from emp
group by MGR
having MGR is not NULL and min(SAL) > 1000
order by min_salary desc;


select DNAME,loc as LOCATION,count(EMPNO) as "NUMBER OF PEOPLE", ROUND(avg(SAL),2) as "AVERAGE SALARY"
from emp,dept
where emp.deptno = dept.deptno
group by DNAME,LOC
union
select DNAME,loc as LOCATION,count(EMPNO) as "NUMBER OF PEOPLE", ROUND(0,2) as "AVERAGE SALARY"
from emp,dept
where dept.deptno not in (select distinct(deptno) from EMP)
group by DNAME,LOC;

