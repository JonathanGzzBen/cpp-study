# animals_oop

Una simple demostración de cómo crear clases, clases abstractas y aprovechar el polimorfismo con C++. Hecho para un stream/clase en el canal de Twitch [Jonark2001](https://www.twitch.tv/jonark2001).

Nótese el uso básico de CMake, el cual no es muy explicado a profundidad, pero es posible darse una idea básica con [este video](https://www.youtube.com/watch?v=V5AEKae4scU), y para algunos usos más interesantes como descargar y usar librerías está [este otro video](https://www.youtube.com/watch?v=fyOCdoesYYU).

## Diseño

Vamos a crear una "clase abstracta", la cual es una clase de la cual no podemos construir objetos directamente. Por ejemplo, supongamos que tenemos una clase abstracta llamada `Figura`, para la cual no podemos determinar el área porque no sabemos qué método usar o qué información tenemos:

```cpp
Figura figura; // Error, no va a dejar compilar
std::cout << figura.area() << std::endl;
```

Seguido de eso, vamos a implementar un par de clases concretas que sean hijas de la clase `Figura`, las cuales puedan implementar sus propios métodos.