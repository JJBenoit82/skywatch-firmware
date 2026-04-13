# skywatch/ext/hello/hello.py
from west.commands import WestCommand

class Hello(WestCommand):
    def __init__(self):
        super().__init__(
            'hello', # west hello
            'prints a greeting', # short help
            'Custom example command.' # long help
        )

    def do_add_parser(self, parser_adder):
        p = parser_adder.add_parser(
            self.name, help=self.help,
            description=self.description)
        # add args here if you want later
        return p

    def do_run(self, args, unknown):
        print("Hello from your custom West command!")