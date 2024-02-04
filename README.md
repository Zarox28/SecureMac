# SecureMac

![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![License: AGPL v3](https://img.shields.io/badge/License-AGPL_v3-blue.svg?style=for-the-badge)
![macOS](https://img.shields.io/badge/mac%20os-000000?style=for-the-badge&logo=macos&logoColor=F0F0F0)

SecureMac is a simple `C++` program that locks the screen and starts a recording with the webcam when it detects a movement.

> Version: **1.1.0**

---

## Table of Contents

- [About](#about)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [How it works](#how-it-works-)
- [Changelog](#changelog)
- [Contributing](#contributing)
- [License](#license)
- [Authors](#authors)

## About ℹ️

SecureMac is a simple `C++` program that locks the screen and starts a recording with the webcam when it detects a movement.\
It's a simple way to protect your computer when you're not in front of it. It's also a good way to know who is using your computer when you're not there.

> Picture this: You're coding away on your Mac, and suddenly, you wish you had a simple, reliable logger to keep track of what's going on.\
That's where `Logger` steps in - a friendly `C++` companion here to make logging messages a breeze. It's like having a trusty sidekick on your coding adventures.\
And guess what? It's open-source, so you can use it for free [here](https://github.com/Zarox28/Logger)! 🎉

> **Note:** This program is only available on macOS.

## Features ✅

- [x] Lock the screen
- [x] Handle mouse inputs
- [x] Start a recording with the webcam
- [x] Stop the recording and the program

- [ ] Play an alarm sound
- [ ] Handle keyboard inputs
- [ ] Detect closed lid

## Installation 🚀

1. Clone the repository

```bash
git clone https://Zarox28/SecureMac.git
```

2. Compile the source code

```bash
make build
```

## Usage ▶️

### Run the program

```bash
make run
```

> **Note:** You can also use the following commands:

- `make run_debug` to run the program in debug mode
- `make clean` to remove the compiled files and video

## How it works 🛠️

When you run the program, it does the following things:

1. Locks the screen
2. Waits for a movement
3. If it detects a movement, it starts a recording with the webcam
4. To stop the recording and the program, you have to enter `Ctrl + C`

## Changelog 📆

see [CHANGELOG.md](CHANGELOG.md) for latest changes.

## Contributing 🤝

Contributions are what make the open source community such an amazing place to learn, inspire, and create. Any contributions you make are **appreciated**, whether it's a simple opinion or a pull request.

See [CONTRIBUTING.md](CONTRIBUTING.md) for more information.

1. Fork the repository
2. Create a new branch (`git checkout -b feature`)
3. Commit your changes (`git commit -m 'Add feature'`)
4. Push to the branch (`git push origin feature`)
5. Create a new Pull Request

## License 📜

This project is licensed under the AGPL v3 License - see the [LICENSE](LICENSE.md) file for details.

## Authors 👨‍💻

- **[@Zarox28](https://github.com/Zarox28)**
