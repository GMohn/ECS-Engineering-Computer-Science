# -*- coding: utf-8 -*-
"""Unit tester for ECS 170 Assignment 5.

Usage: Put this in the folder that contains your implemented perceptron.py, and
    in the same directory, call:

        $ cle

    Do NOT modify anything in this file. Make sure you pass the unit test cases
    before submission.

Authors:
    Fangzhou Li - fzli@ucdavis.edu

"""
import unittest

from perceptron import perceptron


class PerceptronUnitTester(unittest.TestCase):
    """Unit tester class.

    See test_case_1's `result_true` to guide you how to formulate your output.

    Some notes:
        - Your output is a dict containing init and each pass result. This
            means that, if there are 10 passes, then your dict should have 11
            items.
            - The first item of your output should be `init`.
            - The following items are passes beginning with 1, e.g., 1-10 if
                there are 10 passes.
                - Each pass is a list including the training process for each
                    example. This means, if there are 4 examples, then each
                    pass list should have 4 items.

    """
    def test_case_1(self):
        weights = [0.3, -0.6]
        examples = [
            [True, [1, 1]],
            [False, [0, 0]],
            [True, [0, 1]],
            [True, [1, 0]]
        ]

        result_true = {
            'init': {'weights': [0.3, -0.6], 'threshold': 0.4, 'adjustment': 0.09},
            1: [
                {'inputs': [1, 1], 'prediction': False, 'answer': True, 'adjusted_weights': [0.39, -0.51]},
                {'inputs': [0, 0], 'prediction': False, 'answer': False, 'adjusted_weights': [0.39, -0.51]},
                {'inputs': [0, 1], 'prediction': False, 'answer': True, 'adjusted_weights': [0.39, -0.42000000000000004]},
                {'inputs': [1, 0], 'prediction': False, 'answer': True, 'adjusted_weights': [0.48, -0.42000000000000004]}
            ],
            2: [
                {'inputs': [1, 1], 'prediction': False, 'answer': True, 'adjusted_weights': [0.57, -0.33000000000000007]},
                {'inputs': [0, 0], 'prediction': False, 'answer': False, 'adjusted_weights': [0.57, -0.33000000000000007]},
                {'inputs': [0, 1], 'prediction': False, 'answer': True, 'adjusted_weights': [0.57, -0.24000000000000007]},
                {'inputs': [1, 0], 'prediction': True, 'answer': True, 'adjusted_weights': [0.57, -0.24000000000000007]}
            ]
        }
        result_student = perceptron(0.4, 0.09, weights, examples, 2)
        self.assertEqual(result_true, result_student)

    def test_case_2(self):
        weights = [-0.5, 0, 0.5, 0, -0.5]
        examples = [
            [True, [1, 1, 1, 1, 0]],
            [False, [1, 1, 1, 1, 1]],
            [False, [0, 0, 0, 0, 0]],
            [False, [0, 0, 1, 1, 0]],
            [False, [1, 0, 1, 0, 1]],
            [False, [1, 0, 1, 0, 0]],
            [False, [0, 1, 0, 1, 1]],
            [False, [0, 1, 0, 1, 0]],
            [False, [0, 0, 1, 0, 0]],
            [False, [0, 0, 0, 1, 0]],
        ]
        result_true = {
            'init': {'weights': [-0.5, 0, 0.5, 0, -0.5], 'threshold': 0.5, 'adjustment': 0.1},1: [{'inputs': [1, 1, 1, 1, 0], 'prediction': False, 'answer': True, 'adjusted_weights': [-0.4, 0.1, 0.6, 0.1, -0.5]}, {'inputs': [1, 1, 1, 1, 1], 'prediction': False, 'answer': False, 'adjusted_weights': [-0.4, 0.1, 0.6, 0.1, -0.5]}, {'inputs': [0, 0, 0, 0, 0], 'prediction': False, 'answer': False, 'adjusted_weights': [-0.4, 0.1, 0.6, 0.1, -0.5]}, {'inputs': [0, 0, 1, 1, 0], 'prediction': True, 'answer': False, 'adjusted_weights': [-0.4, 0.1, 0.5, 0.0, -0.5]}, {'inputs': [1, 0, 1, 0, 1], 'prediction': False, 'answer': False, 'adjusted_weights': [-0.4, 0.1, 0.5, 0.0, -0.5]}, {'inputs': [1, 0, 1, 0, 0], 'prediction': False, 'answer': False, 'adjusted_weights': [-0.4, 0.1, 0.5, 0.0, -0.5]}, {'inputs': [0, 1, 0, 1, 1], 'prediction': False, 'answer': False, 'adjusted_weights': [-0.4, 0.1, 0.5, 0.0, -0.5]}, {'inputs': [0, 1, 0, 1, 0], 'prediction': False, 'answer': False, 'adjusted_weights': [-0.4, 0.1, 0.5, 0.0, -0.5]}, {'inputs': [0, 0, 1, 0, 0], 'prediction': False, 'answer': False, 'adjusted_weights': [-0.4, 0.1, 0.5, 0.0, -0.5]}, {'inputs': [0, 0, 0, 1, 0], 'prediction': False, 'answer': False, 'adjusted_weights': [-0.4, 0.1, 0.5, 0.0, -0.5]}], 2: [{'inputs': [1, 1, 1, 1, 0], 'prediction': False, 'answer': True, 'adjusted_weights': [-0.30000000000000004, 0.2, 0.6, 0.1, -0.5]}, {'inputs': [1, 1, 1, 1, 1], 'prediction': False, 'answer': False, 'adjusted_weights': [-0.30000000000000004, 0.2, 0.6, 0.1, -0.5]}, {'inputs': [0, 0, 0, 0, 0], 'prediction': False, 'answer': False, 'adjusted_weights': [-0.30000000000000004, 0.2, 0.6, 0.1, -0.5]}, {'inputs': [0, 0, 1, 1, 0], 'prediction': True, 'answer': False, 'adjusted_weights': [-0.30000000000000004, 0.2, 0.5, 0.0, -0.5]}, {'inputs': [1, 0, 1, 0, 1], 'prediction': False, 'answer': False, 'adjusted_weights': [-0.30000000000000004, 0.2, 0.5, 0.0, -0.5]}, {'inputs': [1, 0, 1, 0, 0], 'prediction': False, 'answer': False, 'adjusted_weights': [-0.30000000000000004, 0.2, 0.5, 0.0, -0.5]}, {'inputs': [0, 1, 0, 1, 1], 'prediction': False, 'answer': False, 'adjusted_weights': [-0.30000000000000004, 0.2, 0.5, 0.0, -0.5]}, {'inputs': [0, 1, 0, 1, 0], 'prediction': False, 'answer': False, 'adjusted_weights': [-0.30000000000000004, 0.2, 0.5, 0.0, -0.5]}, {'inputs': [0, 0, 1, 0, 0], 'prediction': False, 'answer': False, 'adjusted_weights': [-0.30000000000000004, 0.2, 0.5, 0.0, -0.5]}, {'inputs': [0, 0, 0, 1, 0], 'prediction': False, 'answer': False, 'adjusted_weights': [-0.30000000000000004, 0.2, 0.5, 0.0, -0.5]}], 3: [{'inputs': [1, 1, 1, 1, 0], 'prediction': False, 'answer': True, 'adjusted_weights': [-0.20000000000000004, 0.30000000000000004, 0.6, 0.1, -0.5]}, {'inputs': [1, 1, 1, 1, 1], 'prediction': False, 'answer': False, 'adjusted_weights': [-0.20000000000000004, 0.30000000000000004, 0.6, 0.1, -0.5]}, {'inputs': [0, 0, 0, 0, 0], 'prediction': False, 'answer': False, 'adjusted_weights': [-0.20000000000000004, 0.30000000000000004, 0.6, 0.1, -0.5]}, {'inputs': [0, 0, 1, 1, 0], 'prediction': True, 'answer': False, 'adjusted_weights': [-0.20000000000000004, 0.30000000000000004, 0.5, 0.0, -0.5]}, {'inputs': [1, 0, 1, 0, 1], 'prediction': False, 'answer': False, 'adjusted_weights': [-0.20000000000000004, 0.30000000000000004, 0.5, 0.0, -0.5]}, {'inputs': [1, 0, 1, 0, 0], 'prediction': False, 'answer': False, 'adjusted_weights': [-0.20000000000000004, 0.30000000000000004, 0.5, 0.0, -0.5]}, {'inputs': [0, 1, 0, 1, 1], 'prediction': False, 'answer': False, 'adjusted_weights': [-0.20000000000000004, 0.30000000000000004, 0.5, 0.0, -0.5]}, {'inputs': [0, 1, 0, 1, 0], 'prediction': False, 'answer': False, 'adjusted_weights': [-0.20000000000000004, 0.30000000000000004, 0.5, 0.0, -0.5]}, {'inputs': [0, 0, 1, 0, 0], 'prediction': False, 'answer': False, 'adjusted_weights': [-0.20000000000000004, 0.30000000000000004, 0.5, 0.0, -0.5]}, {'inputs': [0, 0, 0, 1, 0], 'prediction': False, 'answer': False, 'adjusted_weights': [-0.20000000000000004, 0.30000000000000004, 0.5, 0.0, -0.5]}], 4: [{'inputs': [1, 1, 1, 1, 0], 'prediction': True, 'answer': True, 'adjusted_weights': [-0.20000000000000004, 0.30000000000000004, 0.5, 0.0, -0.5]}, {'inputs': [1, 1, 1, 1, 1], 'prediction': False, 'answer': False, 'adjusted_weights': [-0.20000000000000004, 0.30000000000000004, 0.5, 0.0, -0.5]}, {'inputs': [0, 0, 0, 0, 0], 'prediction': False, 'answer': False, 'adjusted_weights': [-0.20000000000000004, 0.30000000000000004, 0.5, 0.0, -0.5]}, {'inputs': [0, 0, 1, 1, 0], 'prediction': False, 'answer': False, 'adjusted_weights': [-0.20000000000000004, 0.30000000000000004, 0.5, 0.0, -0.5]}, {'inputs': [1, 0, 1, 0, 1], 'prediction': False, 'answer': False, 'adjusted_weights': [-0.20000000000000004, 0.30000000000000004, 0.5, 0.0, -0.5]}, {'inputs': [1, 0, 1, 0, 0], 'prediction': False, 'answer': False, 'adjusted_weights': [-0.20000000000000004, 0.30000000000000004, 0.5, 0.0, -0.5]}, {'inputs': [0, 1, 0, 1, 1], 'prediction': False, 'answer': False, 'adjusted_weights': [-0.20000000000000004, 0.30000000000000004, 0.5, 0.0, -0.5]}, {'inputs': [0, 1, 0, 1, 0], 'prediction': False, 'answer': False, 'adjusted_weights': [-0.20000000000000004, 0.30000000000000004, 0.5, 0.0, -0.5]}, {'inputs': [0, 0, 1, 0, 0], 'prediction': False, 'answer': False, 'adjusted_weights': [-0.20000000000000004, 0.30000000000000004, 0.5, 0.0, -0.5]}, {'inputs': [0, 0, 0, 1, 0], 'prediction': False, 'answer': False, 'adjusted_weights': [-0.20000000000000004, 0.30000000000000004, 0.5, 0.0, -0.5]}]}
        result_student = perceptron(0.5, 0.1, weights, examples, 4)
        self.assertEqual(result_true, result_student)

if __name__ == '__main__':
    unittest.main()
