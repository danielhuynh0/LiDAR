function decodeUplink(input) {
    var distance = (input.bytes[0] | (input.bytes[1] << 8));
    return {
      data: {
        distance: distance
      },
      warnings: [],
      errors: []
    };
  }