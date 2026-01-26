-- Master table
CREATE TABLE item_mstr (
  item_id     NUMBER PRIMARY KEY,
  item_name   VARCHAR2(100),
  balance     NUMBER
);

-- Transaction table
CREATE TABLE item_tr (
  tr_id     NUMBER PRIMARY KEY,
  item_id   NUMBER,
  qty       NUMBER,
  tr_date   DATE
);

-- Sample data
INSERT INTO item_mstr VALUES (1, 'Screw', 100);
INSERT INTO item_mstr VALUES (2, 'Nut', 50);

INSERT INTO item_tr VALUES (1001, 1, 10, SYSDATE);
INSERT INTO item_tr VALUES (1002, 3, 5, SYSDATE);

COMMIT;

-- Check data
SELECT * FROM item_mstr;
SELECT * FROM item_tr;

-- MERGE logic
MERGE INTO item_mstr m
USING (
  SELECT item_id, SUM(qty) qty_sum
  FROM item_tr
  GROUP BY item_id
) t
ON (m.item_id = t.item_id)
WHEN MATCHED THEN
  UPDATE SET m.balance = m.balance - t.qty_sum
WHEN NOT MATCHED THEN
  INSERT (item_id, item_name, balance)
  VALUES (t.item_id, 'New_Item_' || t.item_id, -t.qty_sum);

COMMIT;

-- Final check
SELECT * FROM item_mstr ORDER BY item_id;
