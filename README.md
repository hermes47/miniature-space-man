# Miniature Spaceman
A humble attempt at creating an N-body solar system simulation

---
## Situation
I am currently learning about programing in C++. I want to work on a 'learning' project before I dive into anything actually useful. It's taken a while to come up with such a project, but this is it. The general aim is to create a Newtonian model of the solar system, and simulate it. It's something that I find interesting and can just work on. A lot of the things I'm going to be doing have probably already been solved and are easily google-able, but I want to work through everything myself.

---
## Steps
A broad overview of the way I'm going to undertake this project follows:
- [ ] Write a series of integrators (Euler, Ralston, RK3, RK4, RK5, Verlet, Leapfrog...) that work on vectors/quaterions (when I figure them out).
- [ ] Setup an Earth-Moon two body system, and simulate it in a data only manner. (Actually, could solve analytically given it'll be a two body problem, then compare simulated results to analytic results.)
- [ ] Investigate time step limits of each of the integrators, and the real-time limits.
- [ ] Extend the system to include the Sun, and re simulate.
- [ ] ...

---
## Progress
2016-02-14:
- Implemented Explicit Runge-Kutta integration based on a given Butcher tableau.
- Added tableau generators for integration methods: Euler, Mid-point, Heun, Ralston, Generic second-order, RK3, RK4, three-eighths rule.
- Implemented Adaptive Runge-Kutta integration based on a given extended Butcher tableau.
- Added tableau generators for adaptive methods: Heun-Euler and Bogacki-Shampine. More to come.
2016-02-20:
- Added a Gauss-Jordon Row Reduction method. Will be useful for solving Newton-Raphson method applied to Vectors of variables, eg as required by implicit integrators.
- Using the row reduction function, added a matrix Inverse calculation function.
- Using the row reduction function, added a simultaneous equation solver.
- Removed stand alone RK type integrators. No need for them.
- Realised that this progress thing is going to basically be the git log.