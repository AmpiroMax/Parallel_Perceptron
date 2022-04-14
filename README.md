# Paralell MLP.

## Терминология:

1. Вектор - это матрица размеров n x 1.
2. matrix = std::vector<std::vector<double>>

## Структура:
___
1.1. Базовый класс для слоя `Layer` - чисто виртуальный. От него будут наследоваться 
классы `SoftMax` и `Linear` и `Sigmoid`;

	class Layer
	{
		public:
		
			virtual matrix forward(const matrix&) = 0;
			virtual matrix backward(const matrix&) = 0;
			virtual ~Layer();
	}

1.2. Класс `Linear` - класс для описания линейного слоя. 

	class Linear : public Layer
	{
		
	}
	
1.3. Класс `SoftMax` - класс для расчёта вероятностей принадлежности к определённой 
категории.

	class SoftMax : public Layer
	{
		
	}

1.4. Класс `Sigmoid` - класс, реализующий сигмоиду.

	class Sigmoid : public Layer
	{
		
	}
___	
2.1. Базовый класс для перемножения матриц `MatrixMultiplicator`. 

	class MatrixMultiplicator
	{
		public:
		
			virtual matrix dot(const matrix& lhs, const matrix& rhs) = 0;
			virtual ~MatrixMultiplicator();
	}
	
2.2. Класс, реализующий линейный кубический алгоритм перемножения матриц `SlowMultiplicator`:

	class SlowMultiplicator : public MatrixMultiplicator
	{
		
	}
	
2.3. Класс, реализующий быстрый линейный алгоритм умножения матриц `FastLinearMultiplicator`:

	class FastLinearMultiplicator : public MatrixMultiplicator
	{
		
	}
	
2.4. Класс, реализующие параллельный алгоритм умножения матриц `ParallelMultiplicator`:

	class ParallelMultiplicator : public MatrixMultiplicator
	{
		
	}
	
