#include <string>
#include <boost/python.hpp>
using namespace boost::python;

class Base
{
	public:
		virtual std::string greet()	
		{
			return "Base";
		}
};
class World: public Base
{
public:
    void set(std::string msg) { this->msg = msg; }
    std::string greet() { return msg; }
    std::string msg;
};
std::string pt(Base* bs)
{
	return bs->greet();	
}
Base* create(int type)
{
	if (type == 0)
	{
		return new Base();
	}
	else
	{
		return new World();
	}
	return NULL;
}
char szBuffer[1024];
object encode_to_buff()
{
	szBuffer[0] = 'h';
	szBuffer[1] = 'e';
	szBuffer[2] = 'l';
	szBuffer[3] = '\0';
	szBuffer[4] = 'a';
	int size = 5;
	PyObject* py_buf = PyBuffer_FromReadWriteMemory(szBuffer, size);
	object retval = object(handle<>(py_buf));
	return retval;
}

void decode_from_buff(PyObject* buffer)
{
	const char *szBf;
	long n;
	int result = PyObject_AsCharBuffer(buffer, &szBf, &n);
	if (0 != result)
	{
		printf("PyObject_AsCharBuffer error!\n");
		return ;
	}
	printf("size %ld\n", n);
	for (int i = 0; i < n; ++i)
	{
		printf("%c", szBf[i]);
	}
	puts("");
}
BOOST_PYTHON_MODULE(hello)
{
	class_<Base>("Base")
		.def("greet", &Base::greet)
		;

    class_<World, bases<Base> >("World")
        .def("greet", &World::greet)
        .def("set", &World::set)
		.def_readwrite("msg", &World::msg)
    ;
	def("create", create, 
			return_value_policy<manage_new_object>());
	def("pt", pt);
	def("encode_to_buff", encode_to_buff);
	def("decode_from_buff", decode_from_buff);
}
