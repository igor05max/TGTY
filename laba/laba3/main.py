import random

from typing import List


class Weight:
    def __init__(self, value: float=1.):
        self.value = value

    def __str__(self):
        return f"{self.value}кг"

    def __eq__(self, other):
        return self.value == other.value


class Item:
    def __init__(self):
        self.value = random.randint(1, 100)

    def __str__(self):
        return f"{self.value}кг"

    def get_value(self, value: float):
        self.value = value


class Scales:
    def __init__(self, weights: List[Weight], item: Item):
        self.weights = weights
        self.item = item

    def __iadd__(self, weight: Weight):
        if isinstance(weight, (int, float)):
            weight = Weight(weight)
        self.weights.append(weight)

    def __isub__(self, weight: Weight):
        if isinstance(weight, (int, float)):
            weight = Weight(weight)
        for i, w in enumerate(self.weights):
            if w == weight:
                print("Удалён:", self.weights.pop(i))
                return
        print("Не найден:", weight)

    def add_weights(self, *args):
        self.weights.extend(args)

    def del_weights(self, *args):
        for w in args:
            self.__isub__(w)

    def get_total_weight(self) -> float:
        res = 0.
        for w in self.weights:
            res += w.value
        return res

    def check_balance(self) -> tuple:
        return self.get_total_weight, self.item.value


def main():
    pass

