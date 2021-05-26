#pragma once
#include "string"


// this module contains class and in here functions for work with complex numbers

// functions:
//      add(a, b) -> (a_R + b_R) + (a_C + b_C)i
//      minus(a, b) -> (a_R - b_R) + (a_C - b_C)i
//      multiply(a, b) -> (a_R * b_C - a_C * b_R) - (a_C * b_C + a_R * b_R)i
//      division(a, b) -> (a_R + b_R) + (a_C + b_C)i
//      multiplyOnAlpha(a, alpha) -> (a_R + b_R) + (a_C + b_C)i


namespace MAIN {
    template <typename T>
    class Complex {
    private:
        T real;
        T im;
    public:
        // Constructors
        Complex(T real, T imaginary) {
            this->real = real;
            this->im = imaginary;
        }
        Complex() :real(0), im(0) {};

        // Getters:
        T getReal() { return real; }
        T getIm() { return im; }

        // Setters:
        void set(T real, T imaginary) {
            this->real = real;
            this->im = imaginary;
        }

        // functions
        Complex add(Complex operand) {
            Complex summ;
            summ.set(this->getReal() + operand.getReal(), this->getIm() + operand.getIm());
            return summ;
        }
        Complex sub(Complex operand) {
            Complex summ;
            summ.set(this->getReal() - operand.getReal(), this->getIm() - operand.getIm());
            return summ;
        }
        Complex multiply(Complex a) {
            Complex c;
            c.set(a.getReal() * this->getReal() - a.getIm() * this->getIm(),
                a.getIm() * this->getReal() + a.getIm() * this->getReal());
            return c;
        }
        Complex multiplyOnAlpha(double alpha) {
            Complex mult;
            double real = alpha * this->getReal();
            double imaginary = alpha * this->getIm();
            mult.set(real, imaginary);
            return mult;
        }

        bool isEqual(Complex operand){
            return is_equal(this->getReal(), operand.getReal()) && is_equal(this->getIm(), operand.getIm());
        }

        // overloading operators
        Complex operator+(Complex operand) {
            return this->add(operand);
        }
        Complex operator-(Complex operand) {
            return this->sub(operand);
        }
        Complex operator*(Complex a) {
            return this->multiply(a);
        }
        Complex operator*(double alpha) {
            return this->multiplyOnAlpha(alpha);
        }
        bool operator==(Complex operand) {
            return this->isEqual(operand);
        }
        bool operator!=(Complex operand) {
            return !this->isEqual(operand);
        }

        std::string toString() {
            return "(" + getReal() + ", " + getIm() + ")";
        }

    };
}
