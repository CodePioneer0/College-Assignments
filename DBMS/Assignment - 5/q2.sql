-- Creating table
CREATE TABLE cust_acct (
    acct_id    NUMBER PRIMARY KEY,
    cust_name  VARCHAR2(100),
    balance    NUMBER(14,2)
);

-- Inserting sample data
INSERT INTO cust_acct VALUES (1, 'Alice',   2500);
INSERT INTO cust_acct VALUES (2, 'Bob',      800);
INSERT INTO cust_acct VALUES (3, 'Chandra', 1500);

COMMIT;

-- View initial data
SELECT * FROM cust_acct;


-- PL/SQL block to deduct 1000 from accounts with balance >= 1000
BEGIN
    UPDATE cust_acct
    SET balance = balance - 1000
    WHERE balance >= 1000;

    COMMIT;
EXCEPTION
    WHEN OTHERS THEN
        ROLLBACK;
        DBMS_OUTPUT.PUT_LINE('Error: ' || SQLERRM);
END;
/

-- Final data after update
SELECT * FROM cust_acct;
