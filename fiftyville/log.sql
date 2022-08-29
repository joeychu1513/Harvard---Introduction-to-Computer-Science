-- Keep a log of any SQL queries you execute as you solve the mystery.

-- check crime scene reports

SELECT * FROM crime_scene_reports
    WHERE year = 2021
        AND month = 7
        AND day = 28
        AND street LIKE "%Humphrey%";

-- Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery
-- Interviews were conducted today with three witnesses who were present at the time
-- each of their interview transcripts mentions the bakery

-- check interview

SELECT * FROM interviews
    WHERE year = 2021
        AND month = 7
        AND day = 28;

--



-- check bakery_security_logs and exiting

SELECT * FROM bakery_security_logs
    WHERE year = 2021
        AND month = 7
        AND day = 28
        AND hour = 10
        AND activity = "exit";

-- check atm_transactions withdrawing money

SELECT * FROM atm_transactions
    WHERE year = 2021
        AND month = 7
        AND day = 28
        AND transaction_type = "withdraw"
        AND atm_location LIKE "%Leggett%";

-- check bank account

SELECT * FROM bank_accounts
    WHERE account_number IN
        (SELECT account_number FROM atm_transactions
            WHERE year = 2021
            AND month = 7
            AND day = 28
            AND transaction_type = "withdraw"
            AND atm_location LIKE "%Leggett%"
        );

-- check phone calls

SELECT * FROM phone_calls
    WHERE year = 2021
        AND month = 7
        AND day = 28
        AND duration <= 60;



-- check phone_calls made

SELECT * FROM people
    WHERE phone_number IN
        (SELECT caller FROM phone_calls
            WHERE year = 2021
            AND month = 7
            AND day = 28);



-- intersect suspect

SELECT * FROM people
    WHERE license_plate IN
        (SELECT license_plate FROM bakery_security_logs
            WHERE year = 2021
            AND month = 7
            AND day = 28
            AND hour = 10
            AND activity = "exit")

INTERSECT

SELECT * FROM people
    WHERE id IN
        (SELECT person_id FROM bank_accounts
            WHERE account_number IN
                (SELECT account_number FROM atm_transactions
                    WHERE year = 2021
                    AND month = 7
                    AND day = 28
                    AND transaction_type = "withdraw"
                    AND atm_location LIKE "%Leggett%")
        )

INTERSECT

SELECT * FROM people
    WHERE phone_number IN
        (SELECT caller FROM phone_calls
            WHERE year = 2021
            AND month = 7
            AND day = 28
            AND duration < 60);

-- three suspect left

-- +--------+--------+----------------+-----------------+---------------+
-- |   id   |  name  |  phone_number  | passport_number | license_plate |
-- +--------+--------+----------------+-----------------+---------------+
-- | 449774 | Taylor | (286) 555-6063 | 1988161715      | 1106N58       |
-- | 514354 | Diana  | (770) 555-1861 | 3592750733      | 322W7JE       |
-- | 686048 | Bruce  | (367) 555-5533 | 5773159633      | 94KL13X       |
-- +--------+--------+----------------+-----------------+---------------+

-- check passport ID


SELECT * FROM passengers
    WHERE passport_number IN (1988161715, 3592750733, 5773159633);

-- check flights

SELECT * FROM flights
    WHERE year = 2021
        AND month = 7
        AND day = 29;

-- combine

SELECT flights.*, passengers.passport_number
FROM flights, passengers
    WHERE passengers.flight_id = flights.id
        AND passport_number IN (1988161715, 3592750733, 5773159633)
        AND flights.year = 2021
        AND flights.month = 7
        AND flights.day = 29;

-- 2 suspect left

-- +--------+--------+----------------+-----------------+---------------+
-- |   id   |  name  |  phone_number  | passport_number | license_plate |
-- +--------+--------+----------------+-----------------+---------------+
-- | 449774 | Taylor | (286) 555-6063 | 1988161715      | 1106N58       |
-- | 686048 | Bruce  | (367) 555-5533 | 5773159633      | 94KL13X       |
-- +--------+--------+----------------+-----------------+---------------+

-- check the receiver of their call

SELECT * FROM phone_calls
    WHERE year = 2021
        AND month = 7
        AND day = 28
        AND duration < 60
        AND caller IN ("(286) 555-6063", "(367) 555-5533");

-- +-----+----------------+----------------+------+-------+-----+----------+
-- | id  |     caller     |    receiver    | year | month | day | duration |
-- +-----+----------------+----------------+------+-------+-----+----------+
-- | 233 | (367) 555-5533 | (375) 555-8161 | 2021 | 7     | 28  | 45       |
-- | 254 | (286) 555-6063 | (676) 555-6554 | 2021 | 7     | 28  | 43       |
-- +-----+----------------+----------------+------+-------+-----+----------+

SELECT * FROM people
    WHERE phone_number in ("(375) 555-8161", "(676) 555-6554");

-- +--------+-------+----------------+-----------------+---------------+
-- |   id   | name  |  phone_number  | passport_number | license_plate |
-- +--------+-------+----------------+-----------------+---------------+
-- | 250277 | James | (676) 555-6554 | 2438825627      | Q13SVG6       |
-- | 864400 | Robin | (375) 555-8161 |                 | 4V16VO0       |
-- +--------+-------+----------------+-----------------+---------------+

-- check if James passport flight

SELECT flights.*, passengers.passport_number
FROM flights, passengers
    WHERE passengers.flight_id = flights.id
        AND passport_number = 2438825627;