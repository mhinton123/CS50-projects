-- Keep a log of any SQL queries you execute as you solve the mystery.
-- get the description of the crime in question
select description
    from crime_scene_reports
        where day = 28
        and month = 7
        and year = 2021
        and street = 'Humphrey Street';

        --Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.
        --time: 10:15
        --place: bakery
        --Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.




-- get all 3 interviews from 28/7/2021 to get more info on the case
select name, transcript
    from crime_scene_reports
        where day = 28
        and month = 7
        and year = 2021;

--| Ruth    DONE | Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.                                                          |
--| Eugene  DONE | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.                                                                                                 |
--| Raymond | As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.




--pull all logs from the bakery withhin 10 mins after the theft
select *
    from bakery_security_logs
    join people on people.license_plate = bakery_security_logs.license_plate
    where day = 28
        and month = 7
        and year = 2021
        and hour = 10
        and minute > 15;

--+-----+------+-------+-----+------+--------+----------+---------------+
--| id  | year | month | day | hour | minute | activity | license_plate |
-+-----+------+-------+-----+------+--------+----------+---------------+
--| 260 | 2021 | 7     | 28  | 10   | 16     | exit     | 5P2BI95       |
--| 261 | 2021 | 7     | 28  | 10   | 18     | exit     | 94KL13X       |
--| 262 | 2021 | 7     | 28  | 10   | 18     | exit     | 6P58WS2       |
--| 263 | 2021 | 7     | 28  | 10   | 19     | exit     | 4328GD8       |
--| 264 | 2021 | 7     | 28  | 10   | 20     | exit     | G412CB7       |
--| 265 | 2021 | 7     | 28  | 10   | 21     | exit     | L93JTIZ       |
--| 266 | 2021 | 7     | 28  | 10   | 23     | exit     | 322W7JE       |
--| 267 | 2021 | 7     | 28  | 10   | 23     | exit     | 0NTHK55       |
--+-----+------+-------+-----+------+--------+----------+---------------+




--get all suspects from above license plates
select name from people where license_plate in (select license_plate
    from bakery_security_logs
    where day = 28
        and month = 7
        and year = 2021
        and hour = 10
        and minute between 14 and 26);

--+---------+
--|  name   |
--+---------+
--| Vanessa |
--| Barry   |
--| Iman    |
--| Sofia   |
--| Taylor  |
--| Luca    |
--| Diana   |
--| Kelsey  |
--| Denise  |
--| Thomas  |
--| Bruce   |
--| Jeremy  |
--+---------+




--look to see who used the ATM on Leggett Street before 10:15?
select name
    from atm_transactions
        join bank_accounts on bank_accounts.account_number = atm_transactions.account_number
        join people on people.id = bank_accounts.person_id
            where day = 28
            and month = 7
            and year = 2021
            and atm_location like 'Leggett Street'
            and transaction_type = 'withdraw';

--+---------+
--|  name   |
--+---------+
--| Vanessa |
--| Barry   |
--| Iman    |
--| Sofia   |
--| Luca    |
--| Diana   |
--| Kelsey  |
--| Bruce   |
--| Sophia  |
--+---------+




--suspects who was leaving the bakery 10 minutes after the crime  @ 10:15 AND seen at the ATM before 10:15 on Leggett Street

--+---------+
--|  name   |
--+---------+
--| Bruce   |
--| Diana   |
--| Iman    |
--| Luca    |
--+---------+




--look at phone logs on 28/7/2021 , which were less than a minute long
select *
    from phone_calls
    join people on people.phone_number = phone_calls.caller
    where day = 28
    and month = 7
    and year = 2021
    and duration <= 60
    and name in ('Bruce', 'Diana', 'Iman', 'Luca', 'Taylor');

--+----------------+----------------+--------+----------------+
--|     caller     |    receiver    |  name  |  phone_number  |
--+----------------+----------------+--------+----------------+
--| (367) 555-5533 | (375) 555-8161 | Bruce  | (367) 555-5533 |
--| (286) 555-6063 | (676) 555-6554 | Taylor | (286) 555-6063 |
--| (770) 555-1861 | (725) 555-3243 | Diana  | (770) 555-1861 |
--+----------------+----------------+--------+----------------+

--suspects

--+---------+
--|  name   |
--+---------+
--| Bruce   |
--| Diana   |
--+---------+


--find out who purchased the flight tickets for earliest flight out of Fiftyville on 29/7/2021

--+----+--------------+-----------------------------------------+---------------+
--| id | abbreviation |                full_name                |     city      |
--+----+--------------+-----------------------------------------+---------------+
--| 1  | ORD          | O'Hare International Airport            | Chicago       |
--| 2  | PEK          | Beijing Capital International Airport   | Beijing       |
--| 3  | LAX          | Los Angeles International Airport       | Los Angeles   |
--| 4  | LGA          | LaGuardia Airport                       | New York City | <---- Destinaion airport from flight ID 36
--| 5  | DFS          | Dallas/Fort Worth International Airport | Dallas        |
--| 6  | BOS          | Logan International Airport             | Boston        |
--| 7  | DXB          | Dubai International Airport             | Dubai         |
--| 8  | CSF          | Fiftyville Regional Airport             | Fiftyville    |
--| 9  | HND          | Tokyo International Airport             | Tokyo         |
--| 10 | CDG          | Charles de Gaulle Airport               | Paris         |
--| 11 | SFO          | San Francisco International Airport     | San Francisco |
--| 12 | DEL          | Indira Gandhi International Airport     | Delhi         |
--+----+--------------+-----------------------------------------+---------------+

-- find earliest flight to
select name
    from flights
    join passengers on passengers.flight_id = flights.id
    join people on people.passport_number = passengers.passport_number
        where day = 29
        and month = 7
        and year = 2021
        and origin_airport_id = 8
        and flight_id = 36;

--people on the earliest flight out of Fiftyville on 29/7/2021

--+--------+
--|  name  |
--+--------+
--| Doris  |
--| Sofia  |
--| Bruce  |
--| Edward |
--| Kelsey |
--| Taylor |
--| Kenny  |
--| Luca   |
--+--------+

--THIEF <---

--+---------+
--|  name   |
--+---------+
--| Bruce   |
--+---------+

-- get name for accomplice from bruce's phone call after the theft
select name from people where phone_number = '(375) 555-8161';


+-------+
| name  |
+-------+
| Robin |
+-------+