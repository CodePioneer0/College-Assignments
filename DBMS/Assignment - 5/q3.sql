-- Table and sample data
CREATE TABLE emp (
  emp_id NUMBER PRIMARY KEY,
  ename  VARCHAR2(100),
  salary NUMBER(12,2)
);

INSERT INTO emp VALUES (101, 'Ravi',   20000);
INSERT INTO emp VALUES (102, 'Maya',   35000);
INSERT INTO emp VALUES (103, 'Vikram', NULL);

COMMIT;

-- Check initial data
SELECT * FROM emp;


-- PL/SQL block: update salaries using a FOR UPDATE cursor
DECLARE
  CURSOR c_emp IS
    SELECT emp_id, salary
    FROM emp
    FOR UPDATE;
  
  v_emp       c_emp%ROWTYPE;
  rows_updated PLS_INTEGER := 0;
BEGIN
  OPEN c_emp;
  LOOP
    FETCH c_emp INTO v_emp;
    EXIT WHEN c_emp%NOTFOUND;

    IF v_emp.salary IS NOT NULL THEN
      UPDATE emp
      SET salary = salary * 1.15
      WHERE CURRENT OF c_emp;

      rows_updated := rows_updated + 1;
      DBMS_OUTPUT.PUT_LINE('Updated emp_id=' || v_emp.emp_id);
    ELSE
      DBMS_OUTPUT.PUT_LINE('Skipped emp_id=' || v_emp.emp_id || ' (salary NULL)');
    END IF;
  END LOOP;

  CLOSE c_emp;
  COMMIT;

  DBMS_OUTPUT.PUT_LINE('Total rows updated: ' || rows_updated);

EXCEPTION
  WHEN OTHERS THEN
    ROLLBACK;
    DBMS_OUTPUT.PUT_LINE('Error: ' || SQLERRM);
END;
/
-- End of PL/SQL block

-- Check final data
SELECT * FROM emp;
