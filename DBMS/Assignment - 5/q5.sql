CREATE TABLE staff_info (
  personnel_id NUMBER PRIMARY KEY,
  full_name VARCHAR2(50),
  salary NUMBER(10, 2)
);

INSERT INTO staff_info VALUES (201, 'Rohit Sharma', 55000);
INSERT INTO staff_info VALUES (202, 'Emily Watson', 48000);
INSERT INTO staff_info VALUES (203, 'Carlos Mendes', NULL);
drop table staff_info;

CREATE OR REPLACE PROCEDURE update_personnel_pay (
  p_personnel_id IN staff_info.personnel_id%TYPE,
  p_amount IN staff_info.salary%TYPE
) IS
  v_salary staff_info.salary%TYPE;
BEGIN
  SELECT salary INTO v_salary
  FROM staff_info
  WHERE personnel_id = p_personnel_id;

  IF v_salary IS NULL THEN
    RAISE_APPLICATION_ERROR(-20002, 'Cannot raise salary. Current salary is NULL.');
  END IF;
  
  UPDATE staff_info
  SET salary = v_salary + p_amount
  WHERE personnel_id = p_personnel_id;
  
  DBMS_OUTPUT.PUT_LINE('Success: Salary updated for ' || p_personnel_id);
  COMMIT;

EXCEPTION
  WHEN NO_DATA_FOUND THEN
    RAISE_APPLICATION_ERROR(-20001, 'Employee ID ' || p_personnel_id || ' not found.');
  WHEN OTHERS THEN
    ROLLBACK;
    DBMS_OUTPUT.PUT_LINE('Error: ' || SQLERRM);
END update_personnel_pay;


BEGIN
  DBMS_OUTPUT.PUT_LINE(CHR(10) || 'Solution 5: Testing procedure...');

  -- Test 1: Salary is NULL
  update_personnel_pay(203, 1000);
  
  -- Test 2: Successful raise
  update_personnel_pay(201, 5000);
  
  -- Test 3: Employee not found
  update_personnel_pay(999, 1000);
  
EXCEPTION
  WHEN OTHERS THEN
    DBMS_OUTPUT.PUT_LINE('Test harness caught error: ' || SQLERRM);
END;


SELECT * FROM staff_info ;
