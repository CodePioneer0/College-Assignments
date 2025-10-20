--Assignment 8
-- CUSTOMER TABLE
CREATE TABLE Customer (
    cust_id INT PRIMARY KEY CHECK (cust_id BETWEEN 100 AND 10000),
    cust_name VARCHAR(100) NOT NULL,
    annual_revenue DECIMAL(12, 2),
    cust_type VARCHAR(20) CHECK (
        cust_type IN (
            'MANUFACTURER',
            'WHOLESALER',
            'RETAILER'
        )
    )
);

-- TRUCK TABLE
CREATE TABLE Truck (
    truck_no INT PRIMARY KEY,
    driver_name VARCHAR(100) NOT NULL
);

-- CITY TABLE
CREATE TABLE City (
    city_name VARCHAR(100) PRIMARY KEY,
    population INT
);

-- SHIPMENT TABLE
CREATE TABLE Shipment (
    shipment_no INT PRIMARY KEY,
    cust_id INT,
    weight DECIMAL(10, 2) CHECK (weight < 1000),
    truck_no INT,
    destination VARCHAR(100),
    ship_date DATE,
    FOREIGN KEY (cust_id) REFERENCES Customer (cust_id) ON DELETE CASCADE,
    FOREIGN KEY (truck_no) REFERENCES Truck (truck_no) ON DELETE SET NULL,
    FOREIGN KEY (destination) REFERENCES City (city_name)
);


select cust_name
from customer, shipment
where customer.cust_id = shipment.cust_id and destination in ('Kolkata','Chennai','Mumbai');

select distinct driver_name
from truck, shipment
where truck.truck_no = shipment.truck_no and weight > 200;

select max(weight) as Max_Weight, min(weight) as Min_Weight
from shipment;

select cust_id, avg(weight) as Avg_Weight
from shipment
group by cust_id;

select DISTINCT city_name,population
from city, shipment
where city.city_name = shipment.destination and weight > 100;

select city_name
from shipment, city
where shipment.destination = city.city_name
group by city_name
having count(distinct cust_id) = ( select count(*) from customer );

select city_name ,max(weight) as Max_Weight
from city,shipment where city_name = destination
group by city_name;

select cust_name,annual_revenue
from customer, shipment,truck
where customer.cust_id = shipment.cust_id and shipment.truck_no = truck.truck_no
and driver_name = 'IQBAL';

select driver_name
from truck,shipment
where shipment.truck_no = truck.truck_no
group by truck.truck_no
having count(distinct destination) = (select count(*) from city);

select city_name,min(weight) as MIN_Weight
from city,shipment
where city_name = destination
and population > 1000000
group by city_name;


