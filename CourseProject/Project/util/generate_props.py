import sys
import os
import glob
import configparser


def parse_properties(file):
    properties = configparser.ConfigParser()
    properties.read(file)
    return properties['Default']


def generate_header(file_name, properties):
    path = sys.argv[1] + '../../include/properties/' + file_name + '.hpp'
    path = os.path.abspath(path)
    if not os.path.exists(os.path.dirname(path)):
        try:
            os.makedirs(os.path.dirname(path))
        except OSError as exc:
            raise
    with open(path, 'w+') as out:
        define = file_name.upper() + '_PROPERTIES_HPP'
        out.write('#ifndef ' + define + '\n')
        out.write('#define ' + define + '\n\n')
        out.write('namespace properties {\n')
        out.write('    namespace ' + file_name + ' {\n')
        for name in properties:
            out.write('        constexpr static char ' + name + '[] = ' + properties[name] + ';\n')
        out.write('    }\n')
        out.write('}\n')
        out.write('\n#endif // ' + define + '\n')


def generate():
    if len(sys.argv) < 2:
        return
    os.chdir(sys.argv[1])
    for file in glob.glob("*.properties"):
        props = parse_properties(file)
        generate_header(file.split('.')[0], props)


if __name__ == '__main__':
    generate()
