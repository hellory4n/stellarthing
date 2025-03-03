package bobx

import (
	"archive/zip"
	"bytes"
	"encoding/json"
	"errors"
	"io"
	"os"
)

// bestest format ever. pretty much just disguised zip + json
type Bobx struct {
	buffer *bytes.Buffer
	writer *zip.Writer
	reader *zip.Reader
	path string
}

// opens or creates a bobx file
func Open(path string) (*Bobx, error) {
	bobessence := &Bobx{
		buffer: new(bytes.Buffer),
		path: path,
	}

	// check if it exists
	if _, err := os.Stat(path); errors.Is(err, os.ErrNotExist) {
		bobessence.writer = zip.NewWriter(bobessence.buffer)
		return bobessence, nil
	}

	bytesma, err := os.ReadFile(path)
	if err != nil {
		return nil, err
	}

	reader, err := zip.NewReader(bytes.NewReader(bytesma), int64(len(bytesma)))
	if err != nil {
		return nil, err
	}
	bobessence.reader = reader

	return bobessence, nil
}

// saves the bobx data to a file
func (b *Bobx) Save() error {
	if b.writer != nil {
		_ = b.writer.Close()
		b.writer = nil
	}

	return os.WriteFile(b.path, b.buffer.Bytes(), 0644) // read/write
}

// writes data to bobx
func (b *Bobx) Write(filename string, data any) error {
	if b.writer == nil {
		b.buffer = new(bytes.Buffer)
		b.writer = zip.NewWriter(b.buffer)
	}

	file, err := b.writer.Create(filename)
	if err != nil {
		return err
	}

	jsonBytes, err := json.MarshalIndent(data, "", "\t")
	if err != nil {
		return err
	}

	_, err = file.Write(jsonBytes)
	if err != nil {
		return err
	}

	if err := b.writer.Close(); err != nil {
		return err
	}
	b.writer = nil

	zipBytes := b.buffer.Bytes()
	b.reader, err = zip.NewReader(bytes.NewReader(zipBytes), int64(len(zipBytes)))
	return err
}

// reads data from bobx and deserializes it into out. if it doesn't exist, it writes using defaultVal
func (b *Bobx) Read(filename string, defaultVal any) (any, error) {
	if b.reader == nil {
		return nil, errors.New("bobx file is not readable")
	}

	for _, file := range b.reader.File {
		if file.Name == filename {
			rc, err := file.Open()
			if err != nil {
				return nil, err
			}
			defer rc.Close()

			jsonData, err := io.ReadAll(rc)
			if err != nil {
				return nil, err
			}

			var rr any
			json.Unmarshal(jsonData, rr)
			return rr, nil
		}
	}

	// doesn't exist :(
	b.Write(filename, defaultVal)
	return b.Read(filename, defaultVal)
}
