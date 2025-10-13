--Assginment - 8
create table Customer(
    cust_id int primary key check(cust_id>=100 and cust_id<=10000),
    cust_name varchar(30) not null,
    annual_revenue decimal(12,2),
    cust_type varchar(20) check(cust_type in ('Manufacturer','Wholesaler','Retailer'))
);
CREATE TABLE Truck (
    truck_no INT PRIMARY KEY,
    driver_name VARCHAR(50) NOT NULL
);
CREATE TABLE City (
    city_name VARCHAR(50) PRIMARY KEY,
    population INT
);
CREATE TABLE Shipment (
    shipment_no INT PRIMARY KEY,
    cust_id INT,
    weight DECIMAL(10,2) CHECK (weight < 1000),
    truck_no INT,
    destination VARCHAR(50),
    ship_date DATE,
    FOREIGN KEY (cust_id) REFERENCES Customer(cust_id) ON DELETE CASCADE,
    FOREIGN KEY (truck_no) REFERENCES Truck(truck_no) ON DELETE SET NULL,
    FOREIGN KEY (destination) REFERENCES City(city_name)
);
INSERT INTO Customer VALUES
(101, 'ABC Industries', 1500000.00, 'MANUFACTURER'),
(102, 'FastSupply Co.', 850000.00, 'WHOLESALER'),
(103, 'CityMart', 450000.00, 'RETAILER'),
(104, 'GlobalTraders', 950000.00, 'WHOLESALER'),
(105, 'Elite Manufacturing', 2000000.00, 'MANUFACTURER'),
(106, 'MetroRetail', 700000.00, 'RETAILER'),
(107, 'StarWholesale', 1200000.00, 'WHOLESALER'),
(108, 'BuildIt Corp', 1800000.00, 'MANUFACTURER'),
(109, 'QuickShop', 520000.00, 'RETAILER'),
(110, 'SuperTrade Ltd', 1100000.00, 'WHOLESALER');
INSERT INTO Truck VALUES
(1, 'IQBAL'),
(2, 'RAHUL'),
(3, 'MEENA'),
(4, 'VIKAS'),
(5, 'ARJUN'),
(6, 'PRIYA'),
(7, 'SANJAY'),
(8, 'KIRAN'),
(9, 'JAVED'),
(10, 'RANI');

INSERT INTO City VALUES
('Kolkata', 14800000),
('Chennai', 10700000),
('Mumbai', 20400000),
('Delhi', 31000000),
('Pune', 7800000),
('Hyderabad', 11000000),
('Bangalore', 12300000),
('Ahmedabad', 8400000),
('Jaipur', 5500000),
('Lucknow', 6800000);

INSERT INTO Shipment VALUES
(1001, 101, 250.00, 1, 'Kolkata', '2025-10-01'),
(1002, 102, 120.00, 2, 'Chennai', '2025-10-02'),
(1003, 103, 180.00, 3, 'Mumbai', '2025-10-03'),
(1004, 104, 950.00, 4, 'Delhi', '2025-10-04'),
(1005, 105, 220.00, 5, 'Pune', '2025-10-05'),
(1006, 106, 450.00, 6, 'Hyderabad', '2025-10-06'),
(1007, 107, 130.00, 7, 'Bangalore', '2025-10-07'),
(1008, 108, 300.00, 8, 'Ahmedabad', '2025-10-08'),
(1009, 109, 650.00, 9, 'Jaipur', '2025-10-09'),
(1010, 110, 275.00, 10, 'Lucknow', '2025-10-10'),
(1011, 101, 190.00, 1, 'Mumbai', '2025-10-11'),
(1012, 102, 210.00, 2, 'Kolkata', '2025-10-12'),
(1013, 103, 800.00, 3, 'Chennai', '2025-10-13'),
(1014, 104, 560.00, 4, 'Hyderabad', '2025-10-14'),
(1015, 105, 340.00, 5, 'Delhi', '2025-10-15'),
(1016, 106, 150.00, 6, 'Pune', '2025-10-16'),
(1017, 107, 240.00, 7, 'Ahmedabad', '2025-10-17'),
(1018, 108, 410.00, 8, 'Mumbai', '2025-10-18'),
(1019, 109, 370.00, 9, 'Kolkata', '2025-10-19'),
(1020, 110, 480.00, 10, 'Chennai', '2025-10-20');




