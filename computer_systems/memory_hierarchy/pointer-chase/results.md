Starting point:

- Data loading: 5.897s
- Computation 2.394s

First change:

- Remove DollarAmount class and directly put dollars and cents fields in the Payment class
  - Data loading: 3.465s
  - Computation 1.859s

Second change:

- Remove Address object and put it directly into User
  - Data loading: 3.162s
  - Computation 1.863s

Third change:

- Remove name from User; don't need to instantiate this when creating object
  - Data loading: 3.076s
  - Computation 1.833s

Fourth change:

- Remove address info because it's not used in the calculation
  - Data loading: 2.916s
  - Computation 1.881s

Fifth change:

- Remove time from Payment because it's not needed
  - Data loading: 2.580s
  - Computation 1.792s

Sixth change:

- Remove user_id from User because it's also not used in the calculation
  - Data loading: 2.559s
  - Computation 1.787s
