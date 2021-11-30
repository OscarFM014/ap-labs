# build & test automation

APP_NAME=earthquake

build:
	go build -o ${APP_NAME}.o ${APP_NAME}.go

test: build
	 @echo Test 1
	./${APP_NAME}.o -p 5 -e 2 || true
	@echo Test 2
	./${APP_NAME}.o || true

clean:
	rm -rf *.o