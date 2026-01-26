
CREATE TABLE circles (
  radius        NUMBER(10,4),
  circumference NUMBER(15,6)
);

DECLARE
  v_radius  NUMBER;
  v_circ    NUMBER;
  pi_const  CONSTANT NUMBER := 3.141592653589793;
  i         PLS_INTEGER;
BEGIN
  FOR i IN 1..10 LOOP
    v_radius := TRUNC(DBMS_RANDOM.VALUE(1, 10), 4);
    v_circ   := TRUNC(2 * pi_const * v_radius, 6);

    INSERT INTO circles (radius, circumference)
    VALUES (v_radius, v_circ);

    DBMS_OUTPUT.PUT_LINE('Inserted radius=' || v_radius ||
                         ' circ=' || v_circ);
  END LOOP;

  COMMIT;
END;
/

-- View results
SELECT * FROM circles;
